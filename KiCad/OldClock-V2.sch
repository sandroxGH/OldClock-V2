EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Altera
LIBS:Msystem
LIBS:motor_drivers
LIBS:79xx-Regler-BuildingBlock_ModB_RevA-cache
LIBS:Switch
LIBS:Display
LIBS:Relay
LIBS:relays
LIBS:nxp
LIBS:dc-dc
LIBS:OldClock-V2-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUINO_as_UNO SH1
U 1 1 5A2EFA49
P 5975 2150
F 0 "SH1" H 5975 900 60  0000 C CNN
F 1 "ARDUINO_as_UNO" H 6000 3500 60  0000 C CNN
F 2 "" H 5775 1925 60  0000 C CNN
F 3 "" H 5775 1925 60  0000 C CNN
	1    5975 2150
	1    0    0    -1  
$EndComp
$Comp
L DS1307 U2
U 1 1 5A2F9669
P 3575 4650
F 0 "U2" H 4150 5825 60  0000 C CNN
F 1 "DS1307" V 4150 5450 60  0000 C CNN
F 2 "" H 3825 4650 60  0001 C CNN
F 3 "" H 3825 4650 60  0001 C CNN
	1    3575 4650
	0    -1   -1   0   
$EndComp
$Comp
L I2c_LCD U3
U 1 1 5A2F99E7
P 4225 4100
F 0 "U3" H 5000 4400 60  0000 C CNN
F 1 "I2c_LCD" H 4550 4200 60  0000 C CNN
F 2 "" H 4175 4100 60  0001 C CNN
F 3 "" H 4175 4100 60  0001 C CNN
	1    4225 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR21
U 1 1 5A2FA069
P 4825 3550
F 0 "#PWR21" H 4825 3300 50  0001 C CNN
F 1 "GND" H 4825 3400 50  0000 C CNN
F 2 "" H 4825 3550 50  0001 C CNN
F 3 "" H 4825 3550 50  0001 C CNN
	1    4825 3550
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR14
U 1 1 5A2FA083
P 3325 3550
F 0 "#PWR14" H 3325 3300 50  0001 C CNN
F 1 "GND" H 3325 3400 50  0000 C CNN
F 2 "" H 3325 3550 50  0001 C CNN
F 3 "" H 3325 3550 50  0001 C CNN
	1    3325 3550
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR3
U 1 1 5A2FA265
P 1375 2250
F 0 "#PWR3" H 1375 2100 50  0001 C CNN
F 1 "+5V" H 1375 2390 50  0000 C CNN
F 2 "" H 1375 2250 50  0001 C CNN
F 3 "" H 1375 2250 50  0001 C CNN
	1    1375 2250
	0    -1   -1   0   
$EndComp
$Comp
L L293D U4
U 1 1 5A2FE8D6
P 5500 5500
F 0 "U4" H 5300 6525 50  0000 R CNN
F 1 "L293D" H 5300 6450 50  0000 R CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 5750 4750 50  0001 L CNN
F 3 "" H 5200 6200 50  0001 C CNN
	1    5500 5500
	1    0    0    -1  
$EndComp
$Comp
L D D3
U 1 1 5A2FED6F
P 6300 4725
F 0 "D3" H 6300 4825 50  0000 C CNN
F 1 "BA159" H 6300 4625 50  0000 C CNN
F 2 "" H 6300 4725 50  0001 C CNN
F 3 "" H 6300 4725 50  0001 C CNN
	1    6300 4725
	0    1    1    0   
$EndComp
$Comp
L D D5
U 1 1 5A2FEEC0
P 6575 4725
F 0 "D5" H 6575 4825 50  0000 C CNN
F 1 "BA159" H 6575 4625 50  0000 C CNN
F 2 "" H 6575 4725 50  0001 C CNN
F 3 "" H 6575 4725 50  0001 C CNN
	1    6575 4725
	0    1    1    0   
$EndComp
$Comp
L D D4
U 1 1 5A2FEF9B
P 6300 5300
F 0 "D4" H 6300 5400 50  0000 C CNN
F 1 "BA159" H 6300 5200 50  0000 C CNN
F 2 "" H 6300 5300 50  0001 C CNN
F 3 "" H 6300 5300 50  0001 C CNN
	1    6300 5300
	0    1    1    0   
$EndComp
$Comp
L D D6
U 1 1 5A2FF024
P 6575 5300
F 0 "D6" H 6575 5400 50  0000 C CNN
F 1 "BA159" H 6575 5200 50  0000 C CNN
F 2 "" H 6575 5300 50  0001 C CNN
F 3 "" H 6575 5300 50  0001 C CNN
	1    6575 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 5100 7050 5100
Wire Wire Line
	6575 4875 6575 5150
Connection ~ 6575 5100
Wire Wire Line
	6000 4900 7050 4900
Wire Wire Line
	6300 4875 6300 5150
Connection ~ 6300 4900
Wire Wire Line
	6300 5450 6575 5450
Wire Wire Line
	6300 4575 6575 4575
$Comp
L +12V #PWR25
U 1 1 5A2FFB8F
P 6300 4575
F 0 "#PWR25" H 6300 4425 50  0001 C CNN
F 1 "+12V" H 6300 4715 50  0000 C CNN
F 2 "" H 6300 4575 50  0001 C CNN
F 3 "" H 6300 4575 50  0001 C CNN
	1    6300 4575
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR26
U 1 1 5A2FFD9B
P 6575 5450
F 0 "#PWR26" H 6575 5200 50  0001 C CNN
F 1 "GND" H 6575 5300 50  0000 C CNN
F 2 "" H 6575 5450 50  0001 C CNN
F 3 "" H 6575 5450 50  0001 C CNN
	1    6575 5450
	1    0    0    -1  
$EndComp
Text GLabel 5000 5300 0    60   Input ~ 0
PWM
Wire Wire Line
	5300 6300 5700 6300
Connection ~ 5400 6300
Connection ~ 5600 6300
$Comp
L GND #PWR24
U 1 1 5A300857
P 5600 6300
F 0 "#PWR24" H 5600 6050 50  0001 C CNN
F 1 "GND" H 5600 6150 50  0000 C CNN
F 2 "" H 5600 6300 50  0001 C CNN
F 3 "" H 5600 6300 50  0001 C CNN
	1    5600 6300
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR23
U 1 1 5A300EAB
P 5600 4500
F 0 "#PWR23" H 5600 4350 50  0001 C CNN
F 1 "+12V" H 5600 4640 50  0000 C CNN
F 2 "" H 5600 4500 50  0001 C CNN
F 3 "" H 5600 4500 50  0001 C CNN
	1    5600 4500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR22
U 1 1 5A300ECF
P 5400 4500
F 0 "#PWR22" H 5400 4350 50  0001 C CNN
F 1 "+5V" H 5400 4640 50  0000 C CNN
F 2 "" H 5400 4500 50  0001 C CNN
F 3 "" H 5400 4500 50  0001 C CNN
	1    5400 4500
	1    0    0    -1  
$EndComp
Text GLabel 5000 4900 0    60   Input ~ 0
DIR
$Comp
L R R6
U 1 1 5A30105C
P 4200 4950
F 0 "R6" V 4280 4950 50  0000 C CNN
F 1 "10K" V 4200 4950 50  0000 C CNN
F 2 "" V 4130 4950 50  0001 C CNN
F 3 "" H 4200 4950 50  0001 C CNN
	1    4200 4950
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5A3010BB
P 3750 5300
F 0 "R5" V 3830 5300 50  0000 C CNN
F 1 "220R" V 3750 5300 50  0000 C CNN
F 2 "" V 3680 5300 50  0001 C CNN
F 3 "" H 3750 5300 50  0001 C CNN
	1    3750 5300
	0    1    1    0   
$EndComp
$Comp
L Q_PNP_BCE Q3
U 1 1 5A301116
P 4100 5300
F 0 "Q3" H 4300 5350 50  0000 L CNN
F 1 "Q_PNP_BCE" H 4300 5250 50  0000 L CNN
F 2 "" H 4300 5400 50  0001 C CNN
F 3 "" H 4100 5300 50  0001 C CNN
	1    4100 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5100 4200 5100
Connection ~ 4200 5100
$Comp
L GND #PWR17
U 1 1 5A301E80
P 4200 5500
F 0 "#PWR17" H 4200 5250 50  0001 C CNN
F 1 "GND" H 4200 5350 50  0000 C CNN
F 2 "" H 4200 5500 50  0001 C CNN
F 3 "" H 4200 5500 50  0001 C CNN
	1    4200 5500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR16
U 1 1 5A301EAA
P 4200 4800
F 0 "#PWR16" H 4200 4650 50  0001 C CNN
F 1 "+5V" H 4200 4940 50  0000 C CNN
F 2 "" H 4200 4800 50  0001 C CNN
F 3 "" H 4200 4800 50  0001 C CNN
	1    4200 4800
	1    0    0    -1  
$EndComp
Text GLabel 3500 5300 0    60   Input ~ 0
DIR
Wire Wire Line
	3500 5300 3600 5300
$Comp
L SW_Push SW3
U 1 1 5A30E703
P 7800 2950
F 0 "SW3" H 7850 3050 50  0000 L CNN
F 1 "Edit" H 7800 2890 50  0000 C CNN
F 2 "" H 7800 3150 50  0001 C CNN
F 3 "" H 7800 3150 50  0001 C CNN
	1    7800 2950
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW2
U 1 1 5A30E974
P 7800 2700
F 0 "SW2" H 7850 2800 50  0000 L CNN
F 1 "Up" H 7800 2640 50  0000 C CNN
F 2 "" H 7800 2900 50  0001 C CNN
F 3 "" H 7800 2900 50  0001 C CNN
	1    7800 2700
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW1
U 1 1 5A30E9EF
P 7800 2450
F 0 "SW1" H 7850 2550 50  0000 L CNN
F 1 "Dw" H 7800 2390 50  0000 C CNN
F 2 "" H 7800 2650 50  0001 C CNN
F 3 "" H 7800 2650 50  0001 C CNN
	1    7800 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6775 2950 7600 2950
Wire Wire Line
	7600 2700 7600 2825
Wire Wire Line
	7600 2825 6775 2825
Wire Wire Line
	6775 2700 7500 2700
Wire Wire Line
	7500 2700 7500 2450
Wire Wire Line
	7500 2450 7600 2450
Wire Wire Line
	8000 2300 8000 2950
$Comp
L GND #PWR28
U 1 1 5A30F0A5
P 8000 2700
F 0 "#PWR28" H 8000 2450 50  0001 C CNN
F 1 "GND" H 8000 2550 50  0000 C CNN
F 2 "" H 8000 2700 50  0001 C CNN
F 3 "" H 8000 2700 50  0001 C CNN
	1    8000 2700
	0    -1   -1   0   
$EndComp
Text GLabel 6775 2325 2    60   Input ~ 0
PWM
Text GLabel 6775 2450 2    60   Input ~ 0
DIR
$Comp
L R 15K1
U 1 1 5A338541
P 4375 1675
F 0 "15K1" V 4455 1675 50  0000 C CNN
F 1 "R" V 4375 1675 50  0000 C CNN
F 2 "" V 4305 1675 50  0001 C CNN
F 3 "" H 4375 1675 50  0001 C CNN
	1    4375 1675
	1    0    0    -1  
$EndComp
$Comp
L LDR03 R7
U 1 1 5A3385D1
P 4375 2050
F 0 "R7" V 4175 2050 50  0000 C CNN
F 1 "LDR03" V 4450 2050 50  0000 C TNN
F 2 "Opto-Devices:Resistor_LDR_10x8.5_RM7.6" V 4550 2050 50  0001 C CNN
F 3 "" H 4375 2000 50  0001 C CNN
	1    4375 2050
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR18
U 1 1 5A338790
P 4375 1525
F 0 "#PWR18" H 4375 1375 50  0001 C CNN
F 1 "+5V" H 4375 1665 50  0000 C CNN
F 2 "" H 4375 1525 50  0001 C CNN
F 3 "" H 4375 1525 50  0001 C CNN
	1    4375 1525
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR19
U 1 1 5A3387C4
P 4375 2200
F 0 "#PWR19" H 4375 1950 50  0001 C CNN
F 1 "GND" H 4375 2050 50  0000 C CNN
F 2 "" H 4375 2200 50  0001 C CNN
F 3 "" H 4375 2200 50  0001 C CNN
	1    4375 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2875 3550 2875 3200
Wire Wire Line
	2875 3200 5225 3200
Wire Wire Line
	3025 3550 3025 3075
Wire Wire Line
	3025 3075 5225 3075
Wire Wire Line
	4525 3550 4525 3075
Connection ~ 4525 3075
Wire Wire Line
	4375 3550 4375 3200
Connection ~ 4375 3200
Wire Wire Line
	4375 1875 4825 1875
Wire Wire Line
	4825 1875 4825 2575
Wire Wire Line
	4825 2575 5225 2575
Wire Wire Line
	4375 1900 4375 1825
Connection ~ 4375 1875
$Comp
L Q_NPN_CBE Q4
U 1 1 5A37E50C
P 8875 1725
F 0 "Q4" H 9075 1775 50  0000 L CNN
F 1 "BD410" H 9125 1525 50  0000 L CNN
F 2 "" H 9075 1825 50  0001 C CNN
F 3 "" H 8875 1725 50  0001 C CNN
	1    8875 1725
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 5A37E57D
P 8525 1725
F 0 "R10" V 8605 1725 50  0000 C CNN
F 1 "220R" V 8525 1725 50  0000 C CNN
F 2 "" V 8455 1725 50  0001 C CNN
F 3 "" H 8525 1725 50  0001 C CNN
	1    8525 1725
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR29
U 1 1 5A37E9D1
P 8975 1925
F 0 "#PWR29" H 8975 1675 50  0001 C CNN
F 1 "GND" H 8975 1775 50  0000 C CNN
F 2 "" H 8975 1925 50  0001 C CNN
F 3 "" H 8975 1925 50  0001 C CNN
	1    8975 1925
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR30
U 1 1 5A37EA62
P 9650 1100
F 0 "#PWR30" H 9650 950 50  0001 C CNN
F 1 "+12V" H 9650 1240 50  0000 C CNN
F 2 "" H 9650 1100 50  0001 C CNN
F 3 "" H 9650 1100 50  0001 C CNN
	1    9650 1100
	0    -1   -1   0   
$EndComp
$Comp
L Screw_Terminal_1x02 J2
U 1 1 5A380BD8
P 9850 1200
F 0 "J2" H 9850 1450 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 9700 1200 50  0000 C TNN
F 2 "" H 9850 975 50  0001 C CNN
F 3 "" H 9825 1200 50  0001 C CNN
	1    9850 1200
	-1   0    0    1   
$EndComp
$Comp
L LED D7
U 1 1 5A380FBB
P 6925 1975
F 0 "D7" H 6925 2075 50  0000 C CNN
F 1 "LED_V" H 6925 1875 50  0000 C CNN
F 2 "" H 6925 1975 50  0001 C CNN
F 3 "" H 6925 1975 50  0001 C CNN
	1    6925 1975
	-1   0    0    1   
$EndComp
$Comp
L LED D8
U 1 1 5A381040
P 7250 1475
F 0 "D8" H 7250 1575 50  0000 C CNN
F 1 "LED_R" H 7250 1375 50  0000 C CNN
F 2 "" H 7250 1475 50  0001 C CNN
F 3 "" H 7250 1475 50  0001 C CNN
	1    7250 1475
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 1475 6775 1475
Wire Wire Line
	7400 1975 7075 1975
$Comp
L R R9
U 1 1 5A381442
P 7550 1975
F 0 "R9" V 7630 1975 50  0000 C CNN
F 1 "R" V 7550 1975 50  0000 C CNN
F 2 "" V 7480 1975 50  0001 C CNN
F 3 "" H 7550 1975 50  0001 C CNN
	1    7550 1975
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 5A3814AB
P 7550 1475
F 0 "R8" V 7630 1475 50  0000 C CNN
F 1 "R" V 7550 1475 50  0000 C CNN
F 2 "" V 7480 1475 50  0001 C CNN
F 3 "" H 7550 1475 50  0001 C CNN
	1    7550 1475
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR27
U 1 1 5A381506
P 7700 1975
F 0 "#PWR27" H 7700 1725 50  0001 C CNN
F 1 "GND" H 7700 1825 50  0000 C CNN
F 2 "" H 7700 1975 50  0001 C CNN
F 3 "" H 7700 1975 50  0001 C CNN
	1    7700 1975
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 J1
U 1 1 5A38CA2F
P 8200 2250
F 0 "J1" H 8200 2400 50  0000 C CNN
F 1 "FaseCTRL" V 8300 2250 50  0000 C CNN
F 2 "" H 8200 2250 50  0001 C CNN
F 3 "" H 8200 2250 50  0001 C CNN
	1    8200 2250
	1    0    0    -1  
$EndComp
Connection ~ 8000 2450
Wire Wire Line
	8000 2200 7400 2200
Wire Wire Line
	7400 2200 7400 2575
Wire Wire Line
	7400 2575 6775 2575
Text GLabel 6775 2100 2    60   Input ~ 0
UPS
$Comp
L R R3
U 1 1 5A873EB0
P 3300 1800
F 0 "R3" V 3380 1800 50  0000 C CNN
F 1 "R" V 3300 1800 50  0000 C CNN
F 2 "" V 3230 1800 50  0001 C CNN
F 3 "" H 3300 1800 50  0001 C CNN
	1    3300 1800
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5A873F07
P 3300 2100
F 0 "R4" V 3380 2100 50  0000 C CNN
F 1 "R" V 3300 2100 50  0000 C CNN
F 2 "" V 3230 2100 50  0001 C CNN
F 3 "" H 3300 2100 50  0001 C CNN
	1    3300 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5225 2700 4075 2700
Wire Wire Line
	4075 2700 4075 1950
Wire Wire Line
	4075 1950 3300 1950
$Comp
L D_Zener D2
U 1 1 5A874073
P 3600 2100
F 0 "D2" H 3600 2200 50  0000 C CNN
F 1 "D_Zener" H 3600 2000 50  0000 C CNN
F 2 "" H 3600 2100 50  0001 C CNN
F 3 "" H 3600 2100 50  0001 C CNN
	1    3600 2100
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR12
U 1 1 5A8745B4
P 3300 1650
F 0 "#PWR12" H 3300 1500 50  0001 C CNN
F 1 "+12V" H 3300 1790 50  0000 C CNN
F 2 "" H 3300 1650 50  0001 C CNN
F 3 "" H 3300 1650 50  0001 C CNN
	1    3300 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 5A874600
P 3300 2250
F 0 "#PWR13" H 3300 2000 50  0001 C CNN
F 1 "GND" H 3300 2100 50  0000 C CNN
F 2 "" H 3300 2250 50  0001 C CNN
F 3 "" H 3300 2250 50  0001 C CNN
	1    3300 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2250 3300 2250
$Comp
L CAPACITOR_POLARISED_RevE_Date15jun2010 C1
U 1 1 5A874C6B
P 2325 2250
F 0 "C1" H 2325 2400 30  0000 C CNN
F 1 "CAPACITOR_POLARISED_RevE_Date15jun2010" H 2825 2450 30  0001 C CNN
F 2 "" H 2325 2250 60  0001 C CNN
F 3 "" H 2325 2250 60  0001 C CNN
	1    2325 2250
	0    1    1    0   
$EndComp
$Comp
L Q_PNP_CBE Q2
U 1 1 5A8755B8
P 1875 2250
F 0 "Q2" H 2075 2300 50  0000 L CNN
F 1 "BC327" H 1675 2400 50  0000 L CNN
F 2 "" H 2075 2350 50  0001 C CNN
F 3 "" H 1875 2250 50  0001 C CNN
	1    1875 2250
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_CBE Q1
U 1 1 5A875735
P 1575 2750
F 0 "Q1" H 1775 2800 50  0000 L CNN
F 1 "BC547" H 1225 2825 50  0000 L CNN
F 2 "" H 1775 2850 50  0001 C CNN
F 3 "" H 1575 2750 50  0001 C CNN
	1    1575 2750
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A875A93
P 1525 2250
F 0 "R2" V 1605 2250 50  0000 C CNN
F 1 "10k" V 1525 2250 50  0000 C CNN
F 2 "" V 1455 2250 50  0001 C CNN
F 3 "" H 1525 2250 50  0001 C CNN
	1    1525 2250
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5A875B9C
P 1225 2750
F 0 "R1" V 1305 2750 50  0000 C CNN
F 1 "220R" V 1225 2750 50  0000 C CNN
F 2 "" V 1155 2750 50  0001 C CNN
F 3 "" H 1225 2750 50  0001 C CNN
	1    1225 2750
	0    1    1    0   
$EndComp
$Comp
L +5VA #PWR7
U 1 1 5A876AB8
P 1975 2450
F 0 "#PWR7" H 1975 2300 50  0001 C CNN
F 1 "+5VA" H 1975 2590 50  0000 C CNN
F 2 "" H 1975 2450 50  0001 C CNN
F 3 "" H 1975 2450 50  0001 C CNN
	1    1975 2450
	-1   0    0    1   
$EndComp
Text GLabel 1075 2750 0    60   Input ~ 0
UPS
$Comp
L GND #PWR5
U 1 1 5A877D92
P 1675 2950
F 0 "#PWR5" H 1675 2700 50  0001 C CNN
F 1 "GND" H 1675 2800 50  0000 C CNN
F 2 "" H 1675 2950 50  0001 C CNN
F 3 "" H 1675 2950 50  0001 C CNN
	1    1675 2950
	1    0    0    -1  
$EndComp
$Comp
L +5VA #PWR11
U 1 1 5A878038
P 3175 3550
F 0 "#PWR11" H 3175 3400 50  0001 C CNN
F 1 "+5VA" H 3175 3690 50  0000 C CNN
F 2 "" H 3175 3550 50  0001 C CNN
F 3 "" H 3175 3550 50  0001 C CNN
	1    3175 3550
	1    0    0    -1  
$EndComp
$Comp
L +5VA #PWR20
U 1 1 5A878B89
P 4675 3550
F 0 "#PWR20" H 4675 3400 50  0001 C CNN
F 1 "+5VA" H 4675 3690 50  0000 C CNN
F 2 "" H 4675 3550 50  0001 C CNN
F 3 "" H 4675 3550 50  0001 C CNN
	1    4675 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 5A879042
P 2325 2450
F 0 "#PWR9" H 2325 2200 50  0001 C CNN
F 1 "GND" H 2325 2300 50  0000 C CNN
F 2 "" H 2325 2450 50  0001 C CNN
F 3 "" H 2325 2450 50  0001 C CNN
	1    2325 2450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR8
U 1 1 5A2FA2F1
P 2325 2050
F 0 "#PWR8" H 2325 1900 50  0001 C CNN
F 1 "+5V" H 2325 2190 50  0000 C CNN
F 2 "" H 2325 2050 50  0001 C CNN
F 3 "" H 2325 2050 50  0001 C CNN
	1    2325 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1975 2050 2325 2050
Connection ~ 2325 2050
Connection ~ 1975 2050
Connection ~ 1675 2250
$Comp
L LM2575-5.0BT U1
U 1 1 5A9733AE
P 1950 6275
F 0 "U1" H 1550 6525 50  0000 L CNN
F 1 "LM2575-5.0BT" H 1950 6525 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-5_Vertical" H 1950 6025 50  0001 L CIN
F 3 "" H 1950 6275 50  0001 C CNN
	1    1950 6275
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR4
U 1 1 5A9735D7
P 1450 6175
F 0 "#PWR4" H 1450 6025 50  0001 C CNN
F 1 "+12V" H 1450 6315 50  0000 C CNN
F 2 "" H 1450 6175 50  0001 C CNN
F 3 "" H 1450 6175 50  0001 C CNN
	1    1450 6175
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR6
U 1 1 5A9736B7
P 1950 6575
F 0 "#PWR6" H 1950 6325 50  0001 C CNN
F 1 "GND" H 1950 6425 50  0000 C CNN
F 2 "" H 1950 6575 50  0001 C CNN
F 3 "" H 1950 6575 50  0001 C CNN
	1    1950 6575
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6550 1450 6550
Wire Wire Line
	1450 6550 1450 6375
Connection ~ 1950 6550
$Comp
L DIODE-STANDARD_RevE_Date15jun2010 D1
U 1 1 5A973A7E
P 2575 6575
F 0 "D1" H 2575 6725 30  0000 C CNN
F 1 "BA159" H 2575 6425 30  0000 C CNN
F 2 "" H 2575 6575 60  0001 C CNN
F 3 "BA159" H 2575 6575 60  0001 C CNN
	1    2575 6575
	0    -1   -1   0   
$EndComp
$Comp
L L L1
U 1 1 5A973B46
P 2825 6375
F 0 "L1" V 2775 6375 50  0000 C CNN
F 1 "L" V 2900 6375 50  0000 C CNN
F 2 "" H 2825 6375 50  0001 C CNN
F 3 "" H 2825 6375 50  0001 C CNN
	1    2825 6375
	0    -1   -1   0   
$EndComp
$Comp
L CAPACITOR_POLARISED_RevE_Date15jun2010 C2
U 1 1 5A973D2E
P 3125 6575
F 0 "C2" H 3125 6725 30  0000 C CNN
F 1 "470uF 25V" H 3150 6450 30  0000 C CNN
F 2 "" H 3125 6575 60  0001 C CNN
F 3 "" H 3125 6575 60  0001 C CNN
	1    3125 6575
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 5A973DD3
P 3400 6525
F 0 "C3" H 3425 6625 50  0000 L CNN
F 1 "220nf" H 3425 6425 30  0000 L CNN
F 2 "" H 3438 6375 50  0001 C CNN
F 3 "" H 3400 6525 50  0001 C CNN
	1    3400 6525
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 6375 2975 6375
Wire Wire Line
	2675 6375 2450 6375
$Comp
L GND #PWR10
U 1 1 5A973F3F
P 3125 6775
F 0 "#PWR10" H 3125 6525 50  0001 C CNN
F 1 "GND" H 3125 6625 50  0000 C CNN
F 2 "" H 3125 6775 50  0001 C CNN
F 3 "" H 3125 6775 50  0001 C CNN
	1    3125 6775
	1    0    0    -1  
$EndComp
Wire Wire Line
	2575 6775 3400 6775
Wire Wire Line
	3400 6775 3400 6675
Connection ~ 3125 6775
$Comp
L +5V #PWR15
U 1 1 5A974320
P 3400 6375
F 0 "#PWR15" H 3400 6225 50  0001 C CNN
F 1 "+5V" H 3400 6515 50  0000 C CNN
F 2 "" H 3400 6375 50  0001 C CNN
F 3 "" H 3400 6375 50  0001 C CNN
	1    3400 6375
	1    0    0    -1  
$EndComp
Connection ~ 3400 6775
Connection ~ 2575 6775
Connection ~ 2450 6375
Connection ~ 2575 6375
Connection ~ 2675 6375
Connection ~ 2975 6375
Connection ~ 3125 6375
Connection ~ 3400 6375
$Comp
L Screw_Terminal_1x02 J3
U 1 1 5A9757CE
P 7250 5000
F 0 "J3" H 7250 5250 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 7100 5000 50  0000 C TNN
F 2 "" H 7250 4775 50  0001 C CNN
F 3 "" H 7225 5000 50  0001 C CNN
	1    7250 5000
	-1   0    0    1   
$EndComp
$Comp
L Screw_Terminal_1x02 J4
U 1 1 5A975AAE
P 1000 5525
F 0 "J4" H 1000 5775 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 850 5525 50  0000 C TNN
F 2 "" H 1000 5300 50  0001 C CNN
F 3 "" H 975 5525 50  0001 C CNN
	1    1000 5525
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR1
U 1 1 5A975B6F
P 1200 5425
F 0 "#PWR1" H 1200 5275 50  0001 C CNN
F 1 "+12V" H 1200 5565 50  0000 C CNN
F 2 "" H 1200 5425 50  0001 C CNN
F 3 "" H 1200 5425 50  0001 C CNN
	1    1200 5425
	0    1    1    0   
$EndComp
$Comp
L GND #PWR2
U 1 1 5A975BFB
P 1200 5625
F 0 "#PWR2" H 1200 5375 50  0001 C CNN
F 1 "GND" H 1200 5475 50  0000 C CNN
F 2 "" H 1200 5625 50  0001 C CNN
F 3 "" H 1200 5625 50  0001 C CNN
	1    1200 5625
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 5A9970D4
P 1675 2400
F 0 "R11" V 1755 2400 50  0000 C CNN
F 1 "220R" V 1675 2400 50  0000 C CNN
F 2 "" V 1605 2400 50  0001 C CNN
F 3 "" H 1675 2400 50  0001 C CNN
	1    1675 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AA24140
P 7700 1475
F 0 "#PWR?" H 7700 1225 50  0001 C CNN
F 1 "GND" H 7700 1325 50  0000 C CNN
F 2 "" H 7700 1475 50  0001 C CNN
F 3 "" H 7700 1475 50  0001 C CNN
	1    7700 1475
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6775 1725 8375 1725
Wire Wire Line
	9650 1300 8975 1300
Wire Wire Line
	8975 1300 8975 1525
$EndSCHEMATC
