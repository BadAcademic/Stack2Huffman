#include "gexception.h"


gexception::gexception (const type& type) {

    switch (type)
    {
		case MemAlloc: m_message = "Memory allocation error"; break;
		case OpenFile: m_message = "Can't open file"; break;
    }
}


const std::string& gexception::message () const noexcept {

    return m_message;
}
