#ifndef __hmc5883l_H
#define __hmc5883l_H

void hmc5883l_init(void);
void hmc5883l_get_data(s16 *mx,s16 *my,s16 *mz);
#endif
