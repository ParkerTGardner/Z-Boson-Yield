#include "vector"
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<vector<UChar_t>>+;
#pragma link C++ class vector<vector<UChar_t>>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<vector<UChar_t>>::iterator;
#pragma link C++ operators vector<vector<UChar_t>>::const_iterator;
#pragma link C++ operators vector<vector<UChar_t>>::reverse_iterator;
#endif
#pragma link C++ class vector<UChar_t>+;
#pragma link C++ class vector<UChar_t>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<UChar_t>::iterator;
#pragma link C++ operators vector<UChar_t>::const_iterator;
#pragma link C++ operators vector<UChar_t>::reverse_iterator;
#endif
#endif
