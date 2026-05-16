#include "iic.h"

md_i2c_init_t g_i2c_h;

uint8_t iic_recv_buf[IIC_REG_NUM];
uint32_t iic_recv_len = sizeof(iic_recv_buf);
uint8_t iic_recv_ind = 0U;

uint8_t iic_send_buf[IIC_REG_NUM] = {0};
uint32_t iic_send_len = sizeof(iic_send_buf);
uint8_t iic_send_ind = 0U;

uint8_t iic_send_add = 0U;

static void i2c_pin_init(void);
static void initialize_i2c_slave(void);

void iic_init(void)
{
	i2c_pin_init();
	initialize_i2c_slave();

	md_i2c_enable_it_evt(I2C1);
	md_i2c_enable_it_err(I2C1);

	MD_I2C_ENABLE(I2C1);

	md_i2c_enable_ack(I2C1);
}

void clear_buf(uint8_t *p)
{
	for (uint8_t i = 0; i < sizeof(p); i++)
	{
		*(p + i) = 0;
	}
}

static void i2c_pin_init(void)
{
	md_gpio_init_t a;

	/*From the machine initialization SCL pins*/
	a.mode = MD_GPIO_MODE_OUTPUT;
	a.odos = MD_GPIO_OPEN_DRAIN; /*Open drain output*/
	a.pupd = MD_GPIO_PUSH_UP;
	//  a.pupd = MD_GPIO_FLOATING;
	a.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
	a.flt = MD_GPIO_FILTER_DISABLE;
	a.type = MD_GPIO_TYPE_CMOS;
	a.func = MD_GPIO_FUNC_2;
	md_gpio_init(I2C_SCL_PORT, I2C_SCL_PIN, &a);

	/*From the machine initialization SDA pin*/
	a.mode = MD_GPIO_MODE_OUTPUT;
	a.odos = MD_GPIO_OPEN_DRAIN; /*Open drain output*/
	a.pupd = MD_GPIO_PUSH_UP;
	//  a.pupd = MD_GPIO_FLOATING;
	a.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
	a.flt = MD_GPIO_FILTER_DISABLE;
	a.type = MD_GPIO_TYPE_CMOS;
	a.func = MD_GPIO_FUNC_2;
	md_gpio_init(I2C_SDA_PORT, I2C_SDA_PIN, &a);

	return;
}

static void initialize_i2c_slave(void)
{
	/*Will the I2C initialization structure is set to the default values*/
	md_i2c_struct_init(&g_i2c_h);

	/*User configuration I2C*/
	g_i2c_h.addr_mode = MD_I2C_ADDR_7BIT;
	g_i2c_h.clk_speed = 4800000;
	g_i2c_h.dual_addr = MD_I2C_DUALADDR_DISABLE;
	g_i2c_h.duty = MD_I2C_DUTYCYCLE_2;
	g_i2c_h.general_call = MD_I2C_GENERALCALL_DISABLE;
	g_i2c_h.stretch = MD_I2C_STRETCH_ENABLE;
	g_i2c_h.own_addr1 = 0x2D << 1;
	/*Initialize the I2C*/
	md_i2c_init(I2C1, &g_i2c_h);

	/*Interrupt priority level*/
	NVIC_SetPriority(I2C1_IRQn, 1);
	NVIC_EnableIRQ(I2C1_IRQn);
}


