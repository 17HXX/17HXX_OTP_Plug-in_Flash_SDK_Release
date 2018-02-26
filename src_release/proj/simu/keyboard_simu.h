
#pragma once

extern u8 kb_simu_is_func_key;
extern u32 kb_simu_pressed_matrix[8];    // normally kb has max 8 rows
extern kb_data_t kb_simu_key_data;

void kb_simu_init(void);


