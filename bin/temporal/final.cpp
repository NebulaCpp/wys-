#include "wlerror.hpp"
#include "wlio.hpp"
#include "wlvector.hpp"
#include "wlmemory.hpp"
#include "wlstring.hpp"
#include "wltype.hpp"
#include "wlutiles.hpp"
using namespace wys;
extern "C" {
#include "wlstringfmt // Include the WLSTD file."
	namespace filesystem{
		struct save_template {
		};
		__declspec(dllexport) void  save( wfile file,  vector<string>  content,  save_template  st) {
	};
};
}