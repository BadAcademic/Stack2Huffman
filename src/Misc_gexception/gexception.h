#ifndef _gexceptionL_
#define _gexceptionL_

#include<string>


class gexception {

public:

	enum type
	{
        MemAlloc,
        OpenFile,
	};

    gexception (const type&);

    const std::string& message () const noexcept;

private:

    std::string m_message;    
};

#endif
