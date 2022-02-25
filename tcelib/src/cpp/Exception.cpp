#include "Exception.hpp"

#include <iostream>

#include "String.hpp"
#include "StackTrace.hpp"

SharedStringPointer Exception::getStackTrace() {
    SharedStringPointer sTrace = makeSharedString();
    String stMsg = st.getStackTrace();

    sTrace->append(stMsg);

    return sTrace;
}

const String Exception::getMsg() {
    String msg;

    msg.append("Exception Thrown: ");
    msg.append(what());
    msg.append(*getStackTrace());

    return msg;
}
