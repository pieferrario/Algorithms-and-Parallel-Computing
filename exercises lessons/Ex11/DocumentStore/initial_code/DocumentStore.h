#ifndef DOCUMENTSTORE_H
#define DOCUMENTSTORE_H

#include <vector>

#include "Document.h"

const unsigned DRAFT_SIZE = 10;

class DocumentStore {

private:
    std::vector<Document> docs;
    std::vector<Document> docsDraft;
    std::size_t size;
    std::size_t curr;
    std::size_t currDraft;

public:
    explicit DocumentStore (std::size_t);
    explicit DocumentStore(const DocumentStore&); // in addition to that we have do develop the copy constructor that takes a DocumentStore as input

    DocumentStore & operator=(const DocumentStore& ); // and an overloaded assignment operator to copy a document store (taken as (const) ref) into another (thus type function is a ref to docstore)
    void addDocument (const Document&);
    void saveAsDraft (const Document&);
    void print () const;


};

#endif /* DOCUMENTSTORE_H */