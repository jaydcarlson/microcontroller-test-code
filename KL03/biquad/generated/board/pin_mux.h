#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/* PORTA12 (number 20), led */
#define BOARD_INITPINS_led_GPIO                                            GPIOA   /*!< GPIO device name: GPIOA */
#define BOARD_INITPINS_led_PORT                                            PORTA   /*!< PORT device name: PORTA */
#define BOARD_INITPINS_led_GPIO_PIN                                          12U   /*!< PORTA pin index: 12 */
#define BOARD_INITPINS_led_PIN_NAME                                        PTA12   /*!< Pin name */
#define BOARD_INITPINS_led_LABEL                                           "led"   /*!< Label */
#define BOARD_INITPINS_led_NAME                                            "led"   /*!< Identifier name */
#define BOARD_INITPINS_led_DIRECTION                    kPIN_MUX_DirectionOutput   /*!< Direction */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
