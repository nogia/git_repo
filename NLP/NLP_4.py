# installing gensim, spaCy

#pip install gensim
#pip install spacy

# using gensim

from gensim import corpora
documents = [u"Football club Arsenal defeat local rivals this weekend.", u"Weekend football frenzy takes over London.", u"Bank open for take over bids after losing millions.", u"London football clubs bid to move to Wembley stadium.", u"Arsenal bid 50 million pounds for striker Kane.", u"Financial troubles result in loss of millions for bank.", u"Western bank files for bankruptcy after financial losses.", u"London football club is taken over by oil millionaire from Russia.", u"Banking on finances not working for Russia."]

import spacy
nlp =  spacy.load('en_core_web_sm')
texts = []
print("Texts")
for document in documents:
    text = []
    doc = nlp(document)
    for w in doc:
        if not w.is_stop and not w.is_punct and not w.like_num:
            text.append(w.lemma_)
    texts.append(text)
print(texts)

print("Dictionary")
dictionary = corpora.Dictionary(texts)
print(dictionary.token2id)

corpus = [dictionary.doc2bow(text) for text in texts]

# TF-IDF representation
from gensim import models
from gensim.models.phrases import Phrases, Phraser
from gensim.corpora import Dictionary
tfidf = models.TfidfModel(corpus)

print("Document")
for document in tfidf[corpus]:
    print(document)

# creating n-grams
bigram = Phrases(texts)
texts = [bigram[line] for line in texts]

dictionary = Dictionary(texts)
print(dictionary.token2id)
corpus = [dictionary.doc2bow(text) for text in texts]


print("Dictionary")
dictionary.filter_extremes(no_below=20, no_above=0.5)
print(dictionary.token2id)
print("End")

