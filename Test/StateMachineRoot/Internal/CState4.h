#ifndef __StateMachineRoot_CState4__H__
#define __StateMachineRoot_CState4__H__

#include "CStateEvtId.h"
#include "CEventBase.h"

#include "Events.h"
#include "EventType2.h"

#include "CData.h"

namespace StateMachineRoot {
   namespace Internal {
      class CState4 : public ILULibStateMachine::CStateEvtId {
         public:
                                               CState4(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData);
                                               ~CState4(void);

         public:
            void                               HandleEventType2ToChild(ILULibStateMachine::SPEventBase spEventBase, const LibEvents::CEventType2Data* const pData);

         private:
                                               CState4(const CState4& ref);
            CState4                            operator=(const CState4& ref);

         private:
            CData*                             m_pData;
            ILULibStateMachine::SPStateMachine m_spStateMachine;
      };
   };
};

#endif //__StateMachineRoot_CState4__H__

