#include "TCreateState.h"

#include "CreateState.h"
#include "CState4.h"

namespace StateMachineRoot {
   namespace Internal {
      void CState4::HandleEventType2ToChild(ILULibStateMachine::SPEventBase  spEventBase, const LibEvents::CEventType2Data* const pData)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState4 glob data [%3%] --> forward event\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal);
         if(!m_spStateMachine->EventHandle(pData, spEventBase)) {
            ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState4 glob data [%3%]: not finished\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal);
            return;
         }
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState4 glob data [%3%]: finished  --> to state 2\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal);
         throw ILULibStateMachine::CStateChangeException("state change to state-2", CreateState2(m_pData));
    }

      ILULibStateMachine::CCreateState CreateState4(CData* pData)
      {
         return ILULibStateMachine::TCreateState<CState4,CData>(pData);
      }
   };
};

