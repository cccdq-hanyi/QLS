#include "node_cfg.h"
#include "../typedef_all.h"

#ifdef comm_user_tx
uint8_t u8_appl_dllcanTxOk(uint32_t id, uint8_t data[], uint8_t len)
{
    return 0;
}
#endif
#ifdef comm_user_rx
uint8_t u8_appl_dllcanRx(uint32_t id, uint8_t data[], uint8_t len)
{
    return 0;
}
#endif
