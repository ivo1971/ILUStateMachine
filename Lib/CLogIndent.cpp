/** @file
 ** @brief The CLogIndent definition.
 **/
#include "Include/CLogIndent.h"
#include "Include/Logging.h"

namespace ILULibStateMachine {
   CLogIndent::CLogIndent(void) {
      LogIndent();
   }
    
   CLogIndent::~CLogIndent(void) {
      LogUnindent();
   }
};

