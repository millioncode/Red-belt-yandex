#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    // Напишите реализацию функции, не копируя объекты типа Token
    vector<Sentence<Token>> sentenceList;
    if (tokens.empty())
    {
        return move(sentenceList);
    }

    Sentence<Token> sentence;
    auto it = begin(tokens);
    while (it != end(tokens))
    {
        bool IsEndSentencePunctuation = (*it).IsEndSentencePunctuation();

        if (IsEndSentencePunctuation)
        {
            do
            {
                sentence.push_back(move(*it));
                ++it;
            } while (it != end(tokens) && (*it).IsEndSentencePunctuation());

            sentenceList.push_back(move(sentence));
        }
        else
        {
            sentence.push_back(move(*it));
            ++it;
        }
    }

    if (!sentence.empty())
    {
        sentenceList.push_back(move(sentence));
    }

    return move(sentenceList);
}


struct TestToken {
        string data;
        bool is_end_sentence_punctuation = false;

        bool IsEndSentencePunctuation() const {
            return is_end_sentence_punctuation;
        }
        bool operator==(const TestToken& other) const {
            return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
        }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
                vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                            })
                );

    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
                vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                            })
                );

    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
                vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                                {{"Without"}, {"copies"}, {".", true}},
                                            })
                );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}
