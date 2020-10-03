# tja1145--raw-register-parser
tja1145 -raw-register-parser

tja1145 raw register value blob parser tja1145 binary register value blob parser (interpreter)

That is a utility tool to interpret the raw binary tja1145 registers values blob to human readable *.txt configuration report according the tja1145 datasheet. As a example there are data-in and data-out for tja1145 *.txt. Users all over the world may appreciate that diagnostic tool and such support of tja1145.

1 The tja1145 registers values themselves must be read from tja1145 chip via SPI bus to MCU RAM.
2 Then binary blob must be transfered from MCU RAM to PC disc (in txt file) via UART,RS232, 100-Base-TX, Bluetooth, WiFi, CAN or any other interface.
3 Finaly on PC that utility can instantly interpret chip settings and reveal honest tja1145 configuration.

Thus developers will get the entire bird's eye view representation of chip configuration.

That is a very handy tool for diagnostic and bug search. 
For example you can open WinMerge.exe and compare correct and faulty configuration and reveal the cause of malfunction
