#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

#include <deque>
#include <string_view>
using namespace std;

class InvertedIndex {
    public:
        // создам конструктор - принимает поток файлов
        InvertedIndex() = default ;
        explicit InvertedIndex(istream& is);

        //void Add(const string& document);
        // заменю лист на дек
        struct Entry {
                size_t docid;
                size_t rating;
        };
        const vector<Entry>& Lookup(string_view word) const ;

        const deque<string>& GetDocument() const {
            return docs;
        }

    private:
        // // заменю лист на дек
        map <string_view, vector<Entry> > index;
        // заменю на deque, string_view?
        deque<string> docs;
};
/*
 * непосредственно сам поиск
 * */
class SearchServer {
    public:
        SearchServer() = default;
        /*
         * принимает поток документов
         * один документ = одна строка
         * */
        explicit SearchServer(istream& document_input):index(document_input) {}
        /*
         * заменяет базу док-ов на новую
*/
        void UpdateDocumentBase(istream& document_input);
        /*
         * метод непосредственного поиска
         * результат = максимум 5 док-ов
         * [текст запроса]: {docid: <значение>, hitcount: <значение>}
         * {docid: <значение>, hitcount: <значение>} ...,
         *  где docid — идентификатор документа (см. ниже),
         * а hitcount — значение метрики релевантности для данного документа
         * (то есть суммарное количество вхождений всех слов запроса в данный документ).
*/
        void AddQueriesStream(istream& query_input, ostream& search_results_output);

    private:
        InvertedIndex index;
};
