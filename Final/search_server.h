#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
using namespace std;

class InvertedIndex {
    public:
        void Add(const string& document);
        list<size_t> Lookup(const string& word) const;

        const string& GetDocument(size_t id) const {
            return docs[id];
        }

    private:
        // ????
        map<string, list<size_t>> index;
        vector<string> docs;
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
        explicit SearchServer(istream& document_input);
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
