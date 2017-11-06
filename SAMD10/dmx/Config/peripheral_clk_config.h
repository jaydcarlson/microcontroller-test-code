/* Auto-generated config file peripheral_clk_config.h */
#ifndef PERIPHERAL_CLK_CONFIG_H
#define PERIPHERAL_CLK_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

/**
 * \def CONF_CPU_FREQUENCY
 * \brief CPU's Clock frequency
 */
#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 12001280
#endif

// <y> Core Clock Source
// <id> core_gclk_selection

// <GCLK_CLKCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_CLKCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_CLKCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_CLKCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_CLKCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_CLKCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <i> Select the clock source for CORE.
#ifndef CONF_GCLK_SERCOM0_CORE_SRC
#define CONF_GCLK_SERCOM0_CORE_SRC GCLK_CLKCTRL_GEN_GCLK0_Val
#endif

// <y> Slow Clock Source
// <id> slow_gclk_selection

// <GCLK_CLKCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_CLKCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_CLKCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_CLKCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_CLKCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_CLKCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <i> Select the slow clock source.
#ifndef CONF_GCLK_SERCOM0_SLOW_SRC
#define CONF_GCLK_SERCOM0_SLOW_SRC GCLK_CLKCTRL_GEN_GCLK1_Val
#endif

/**
 * \def CONF_GCLK_SERCOM0_CORE_FREQUENCY
 * \brief SERCOM0's Core Clock frequency
 */
#ifndef CONF_GCLK_SERCOM0_CORE_FREQUENCY
#define CONF_GCLK_SERCOM0_CORE_FREQUENCY 12001280
#endif

/**
 * \def CONF_GCLK_SERCOM0_SLOW_FREQUENCY
 * \brief SERCOM0's Slow Clock frequency
 */
#ifndef CONF_GCLK_SERCOM0_SLOW_FREQUENCY
#define CONF_GCLK_SERCOM0_SLOW_FREQUENCY 32768
#endif

// <y> TCC Clock Source
// <id> tcc_gclk_selection

// <GCLK_CLKCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_CLKCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_CLKCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_CLKCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_CLKCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_CLKCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <i> Select the clock source for TCC.
#ifndef CONF_GCLK_TCC0_SRC
#define CONF_GCLK_TCC0_SRC GCLK_CLKCTRL_GEN_GCLK0_Val
#endif

/**
 * \def CONF_GCLK_TCC0_FREQUENCY
 * \brief TCC0's Clock frequency
 */
#ifndef CONF_GCLK_TCC0_FREQUENCY
#define CONF_GCLK_TCC0_FREQUENCY 12001280
#endif

// <<< end of configuration section >>>

#endif // PERIPHERAL_CLK_CONFIG_H
