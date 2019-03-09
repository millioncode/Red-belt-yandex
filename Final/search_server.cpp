#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

#include <numeric>

#include <vector>
void LeftStrip(string_view& sv) {
  // удаляем лишние пробелы слева
  while (!sv.empty() && isspace(sv[0])) {
    sv.remove_prefix(1);
  }
}
string_view ReadToken(string_view& sv) {
    LeftStrip(sv);
    // ищем пробел
    // т.е. позицию конца слова - мы ведь сначала удалили пробелы
    auto pos = sv.find(' ');
    // создаем слово
    auto word = sv.substr(0, pos);
    // удаляем слово и
    sv.remove_prefix(pos != sv.npos? pos:sv.size() );
    return word;
}

vector<string_view> SplitIntoWords(string_view line) {
    vector<string_view> value;
    /* читаем строку(содержимое файла
     * за одну итерацию читаем слово
     * добавляем слово в вектор
     * */
    for( string_view word = ReadToken(line); !word.empty() ; word = ReadToken(line)) {
        value.push_back(word);
    }
    return value;
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    index = InvertedIndex(document_input);
    // ??? |
}

void SearchServer::AddQueriesStream(
        istream& query_input, ostream& search_results_output
        ) {
    const auto& documents = index.GetDocument();
    vector<size_t> docid_count(documents.size());
    vector <int64_t> docids(documents.size());
    for (string current_query; getline(query_input, current_query); ) {
        vector<string_view> words;
        words = SplitIntoWords(current_query);
        docid_count.assign(docid_count.size(), 0);

        for (const auto& word : words) {
            for (const auto& [docid, rating]: index.Lookup(word)) {
                docid_count[docid]+= rating;
            }
        }

        iota(docids.begin(), docids.end(), 0);

        partial_sort(
                begin(docids),
                Head(docids, 5).end(),
                end(docids),
                [&docid_count](int64_t lhs, int64_t rhs) {
                  return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
                }
        );
        search_results_output << current_query << ':';
                for (size_t docid : Head(docids, 5)) {
                  const size_t hit_count = docid_count[docid];
                  if (hit_count == 0) {
                break;
                  }

                  search_results_output << " {"
                  << "docid: " << docid << ", "
                  << "hitcount: " << hit_count << '}';
                }
                search_results_output << '\n';

    }
}
InvertedIndex::InvertedIndex(istream& stream) {
    // читаем поток файлов в current_document
    for(string current_document; getline(stream, current_document); ){
        docs.push_back(move(current_document));
        // сохраняю идентификатор этого файла
        size_t docid = docs.size() - 1;
        // файл теперь в базе - читаем из него текст
        for (string_view word : SplitIntoWords(docs.back()) ) {
            // ????
            auto& docids = index[word];
            // docid - не только Id файла из потока,
            // но и расположение в векторе index
            if (!docids.empty() && docids.back().docid==docid ) {
                docids.back().rating++;
            } else {
                docids.push_back({docid, 1});
            }
        }
    }
}

/*void InvertedIndex::Add(const string& document) {
    docs.push_back(document);

    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(document)) {
        index[word].push_back(docid);
    }
}*/

const vector<InvertedIndex::Entry>& InvertedIndex::Lookup(string_view word) const {
    // нахуя статик ???
    static vector<InvertedIndex::Entry> result;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return result;
    }
}
