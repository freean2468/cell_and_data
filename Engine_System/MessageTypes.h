#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

enum message_type
{
	// SYSTEM
	Msg_System,

  // Event
  Msg_Senario,
  Msg_SenarioEnd,
  Msg_Ending,

  // UI
  Msg_Active,
	Msg_InActive,
  Msg_Close,

	Msg_True,
	Msg_False,
};

#endif