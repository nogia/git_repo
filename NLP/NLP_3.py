import spacy
nlp =  spacy.load('en_core_web_sm')

doc = nlp(u'This is a sentence.')
# Using particular model

import en_core_web_sm
nlp = en_core_web_sm.load()
doc = nlp(u'This is a sentence.')

# Constructing tokenizer
nlp =  spacy.load('en_core_web_sm')
#nlp.tokenizer = my_tokenizer

# printing POS
print("POS")
doc = nlp(u'John and I went to the park’')
for token in doc:
    print(token.text, token.pos_)

# printing POS
print("POS")
doc = nlp(u'John and I went to the park’')
for token in doc:
    print(token.text, token.pos_)

# printing NER
print("NER")
doc = nlp(u'Microsoft has offices all over Europe.')
for ent in doc.ents:
    print(ent.text, ent.start_char, ent.end_char, ent.label_)

# Adding stop words

my_stop_words = [u'say', u'be', u'said', u'says', u'saying']
for stopword in my_stop_words:
    lexeme = nlp.vocab[stopword]
    lexeme.is_stop = True

# pre-processing text

doc = nlp(u'The horse galloped down the field and past the river.')
print("Sentence")
sentence = []
for w in doc:
    # if it's not a stop word or punctuation mark, add it to our article!
    if w.text != '\n' and not w.is_stop and not w.is_punct and not w.like_num:
        # we add the lematized version of the word
        sentence.append(w.lemma_)
print(sentence)

