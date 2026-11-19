#include "DocumentStore.h"

DocumentStore::DocumentStore (std::size_t s): docs(s), docsDraft(DRAFT_SIZE), size(s), curr(0), currDraft(0) {}
// we know that docs' size is chosen by the user; draft size is set to 10.

DocumentStore::DocumentStore (const DocumentStore& Document_Store): docs(Document_Store.docs), docsDraft(DRAFT_SIZE), size(Document_Store.size), curr(Document_Store.curr), currDraft(Document_Store.currDraft) {}
DocumentStore & DocumentStore::operator= (const DocumentStore & Document_Store)
{
    if (this != & Document_Store)
    {
        docs = Document_Store.docs;
        docsDraft = Document_Store.docsDraft;
        size = Document_Store.size;
        curr = Document_Store.curr;
        currDraft = Document_Store.currDraft;
    }
    return *this;
}

void DocumentStore::addDocument (const Document& doc)
{
    if (curr == size) // docs.size will not be greater than the requested size. if so, no action should be taken.
    {
        return;
    }
    // else, we add doc to the vector via push_back.
    docs[curr++] = doc;
}

void DocumentStore::saveAsDraft (const Document& draft)
{
  if (curr == DRAFT_SIZE) // the draft is complete and shall be converted as doc.
  {
      return;
  }
  docsDraft[currDraft++] = draft;
}

void DocumentStore::print () const
{
    std::cout << "List of Documents:" << std::endl;
    for (std::size_t j = 0; j < curr; ++j)
        docs[j].print();

    std::cout << "List of Drafts:" << std::endl;
    for (std::size_t j = 0; j < currDraft; ++j)
        docsDraft[j].print();
}
