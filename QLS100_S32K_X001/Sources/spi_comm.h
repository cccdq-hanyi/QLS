
#include <stdint.h>

#ifndef SOURCES_SPI_COMM_H_
#define SOURCES_SPI_COMM_H_

#define SRESULTS_LEN sizeof(qls_results_members) //spi send data length words

#define SPI_STATUS_ERR_DIR0_LOWLEVEL_NOTREACHED      0x0001
#define SPI_STATUS_ERR_DIR0_HIGHLEVEL_REACHED       0x0002
#define SPI_STATUS_ERR_DIR0_MEAS_TIMEOUT            0x0004
#define SPI_STATUS_ERR_DIR1_LOWLEVEL_NOTREACHED      0x0040
#define SPI_STATUS_ERR_DIR1_HIGHLEVEL_REACHED       0x0080
#define SPI_STATUS_ERR_DIR1_MEAS_TIMEOUT            0x0100
#define SPI_STATUS_ERR_MEAS_TOOFAST                 0x1000
#define SPI_STATUS_MEAS_TYPE                        0x2000
#define SPI_STATUS_CALCULATION_ERROR                0x4000

#define SPI_BUFFER_SIZE (sizeof(qls_results_members))
#define SPICOMM_TIMEOUT 20U
typedef struct QLS_RESULTS_MEMBERS {
  uint16_t status;//t_results.members.status
  uint16_t temp_ultrasonic;//t_results.members.temperature_pt0
  uint16_t temp_environment;//t_results.members.temperature_pt1
  uint64_t tof_concentration; //t_results.members.usm_dir0A
  uint64_t tof_level;//t_results.members.usm_dir1A
} qls_results_members;
typedef union QLS_RESULTS {
	qls_results_members members;
  uint16_t words[(SRESULTS_LEN)/2];
} qls_results;

extern qls_results results;
void spi_comm_Spi_Init(void);
uint8_t spi_comm_Spi_Transfer(void);
#endif /* SOURCES_SPI_COMM_H_ */
