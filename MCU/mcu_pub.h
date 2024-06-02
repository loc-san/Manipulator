#ifndef _MCU_PUB_H_
#define _MCU_PUB_H_

#ifndef _BIT_SET_H_
#include <bitset>
#endif

/*
*********************************************************************************
* define
*********************************************************************************
*/
#define	E_OK			0u
#define E_NOT_OK		1u

/*
*********************************************************************************
* type defs and enums
*********************************************************************************
*/

enum PORT : uint8 { PORTA, PORTB, PORTC, PORTD, PORTE };

enum PIN : uint8 {
	PIN_POSITION_0,
	PIN_POSITION_1,
	PIN_POSITION_2,
	PIN_POSITION_3,
	PIN_POSITION_4,
	PIN_POSITION_5,
	PIN_POSITION_6,
	PIN_POSITION_7
};


/*
*********************************************************************************
* Prototypes
*********************************************************************************
*/


struct TIMER {
	uint32 tiStrd;    /* store value of timer */
};


/* Data buffer are used to store connection between MCU and Driver */
struct StrdMcuCnctn {
	PORT port[5];
	PIN firstPin[5];
	PIN secondPin[5];
	Driver* CnctdDrvr[5] = { nullptr };
};

extern std::atomic<uint32> tiStrdTimer;

class MCU {
private:
	std::string		m_model{};					/* Name of the MCU's model				 */
	status			m_stPower;					/* Status of MCU's power				 */
	std::bitset<8>	m_PortA{ 0b0000'0000 };		
	std::bitset<8>	m_PortB{ 0b0000'0000 };
	std::bitset<8>	m_PortC{ 0b0000'0000 };
	std::bitset<8>	m_PortD{ 0b0000'0000 };
	std::bitset<8>	m_PortE{ 0b0000'0000 };
	TIMER			m_timer[5];					/* Timer's data buffer					 */
	StrdMcuCnctn	m_mapping;					/* Store connection between MCU & Driver */

public:
	/* Constructor */
	MCU(std::string model, status stPower)
		: m_model{model}, m_stPower{stPower}
	{
		/* Do nothing */
	};

	/* -- behavior function to turn on digital value of PIN ------------------------------------ */
	void set_bit(PORT port, PIN pinPos);
	/* -- behavior function to turn off digital value of PIN ----------------------------------- */
	void reset_bit(PORT port, PIN pinPos);
	/* -- behavior function to flip current digial value of PIN -------------------------------- */
	void flip_bit(PORT port, PIN pinPos);
	/* -- behavior function to get timer's value of MCU ---------------------------------------- */
	uint32 GetSwTimer() { return tiStrdTimer; };
	/* -- behavior function that allow timer start storing value ------------------------------- */
	void StartSwTimer(TIMER timer[], uint8 index) { timer[index].tiStrd = GetSwTimer(); };
	/* -- behavior function to stop timer counting --------------------------------------------- */
	void StopSwTimer(TIMER timer[], uint8 index) { timer[index].tiStrd = 0; };
	/* -- behavior function to get the duration that timer counted ----------------------------- */
	uint32 DiffSwTimer(TIMER timer[], uint8 index) { return (GetSwTimer() - timer[index].tiStrd); };
	/* -- friend function: mapping PIN/PORT from MCU to Driver --------------------------------- */
	friend uint8 MpgPinLogic(MCU& mcu, PORT port, PIN firstPin, PIN secondPin, Driver& driver);
	/* ----------- Access Function set value for MCU's power ----------------------------------- */
	void setstPower(const status stPower) { m_stPower = stPower; };
	/* ----------- Access Function get value for MCU's power ----------------0------------------ */
	status getstPower() { return m_stPower; };
};

#endif //_MCU_PUB_H_