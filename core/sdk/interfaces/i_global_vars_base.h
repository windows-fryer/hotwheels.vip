#pragma once

class i_global_vars_base
{
public:
	float			m_real_time;					//0x00
	int				m_frame_count;				//0x04
	float			m_abs_frame_time;				//0x08
	float			m_abs_frame_start_time;		//0x0C
	float			m_current_time;				//0x10
	float			m_frame_time;				//0x14
	int				m_max_clients;				//0x18
	int				m_tick_count;					//0x1C
	float			m_interval_per_tick;			//0x20
	float			m_interpolation_amount;		//0x24
	int				m_frame_simulation_ticks;		//0x28
	int				m_network_protocol;			//0x2C
	void* m_save_data;					//0x30
	bool			m_client;					//0x34
	bool		    m_remote_client;				//0x35
	int				m_timestamp_networking_base;	//0x36
	int				m_timestamp_randomize_window;	//0x3A
}; // Size: 0x3E