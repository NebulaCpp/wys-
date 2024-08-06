#include "wlerror.hpp"
#include "wlio.hpp"
#include "wlvector.hpp"
#include "wlmemory.hpp"
#include "wlstring.hpp"
#include "wltype.hpp"
#include "wlutiles.hpp"
using namespace wys;
extern "C" {
	__declspec(dllexport) void  _entry( string argv) {
	 string   msg =  "Hello\n";
	printf(msg);
};
}