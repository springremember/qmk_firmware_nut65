// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PIN A9     // USART TX pin
#define SERIAL_USART_RX_PIN A10     // USART RX pin
#define SERIAL_USART_CONFIG {115200, 3, 0, 0, 0};
#define SERIAL_USART_FULL_DUPLEX
#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_DEBUG
