
#include "../tl_common.h"

#if(MODULE_ETH_ENABLE)
#include "ip_adapt_i.h"

void ipa_set_my_mac(u8 *mac){
	u8 *my_mac = ipa_get_my_mac();
	assert((((int)mac) >> 2) << 2 == ((int)mac));			// address must alighn to 4
	assert((((int)my_mac) >> 2) << 2 == ((int)my_mac));	// address must alighn to 4
	*(u32*)my_mac = *(u32*)mac;
	*(u16*)(my_mac+4) = *(u16*)(mac+4);
}

void ipa_set_my_ip(u8 *ip){
	u8 *my_ip = ipa_get_my_ip();
	assert((((int)ip) >> 2) << 2 == ((int)ip));			// address must alighn to 4
	assert((((int)my_ip) >> 2) << 2 == ((int)my_ip));		// address must alighn to 4
	*((u32*)my_ip) = *((u32*)ip);
}

void ipa_set_gateway(u8 *ip){
	u8 *my_ip = ipa_get_gateway();
	assert((((int)ip) >> 2) << 2 == ((int)ip));			// address must alighn to 4
	assert((((int)my_ip) >> 2) << 2 == ((int)my_ip));		// address must alighn to 4
	*((u32*)my_ip) = *((u32*)ip);
}

void ipa_set_netmask(u8 *ip){
	u8 *my_ip = ipa_get_netmask();
	assert((((int)ip) >> 2) << 2 == ((int)ip));			// address must alighn to 4
	assert((((int)my_ip) >> 2) << 2 == ((int)my_ip));		// address must alighn to 4
	*((u32*)my_ip) = *((u32*)ip);
}

#endif

//  stub, use for telnetd application. called when received a input command
void shell_input(char *cmd, int len){
}


