EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 7874 9449
encoding utf-8
Sheet 1 1
Title "Diode Ring Mixer"
Date "2020-03-06"
Rev "1.2.0"
Comp "CNSIT"
Comment1 "Jony Zhu"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R1
U 1 1 5B2BC82A
P 2300 2950
F 0 "R1" V 2380 2950 50  0000 C CNN
F 1 "150" V 2300 2950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.29x1.40mm_HandSolder" H 2230 2950 50  0001 C CNN
F 3 "" H 2300 2950 50  0000 C CNN
	1    2300 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5B2BC9B5
P 2700 2950
F 0 "R3" V 2780 2950 50  0000 C CNN
F 1 "150" V 2700 2950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.29x1.40mm_HandSolder" H 2630 2950 50  0001 C CNN
F 3 "" H 2700 2950 50  0000 C CNN
	1    2700 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5B2BCA0F
P 2500 2750
F 0 "R2" V 2580 2750 50  0000 C CNN
F 1 "37" V 2500 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.29x1.40mm_HandSolder" H 2430 2750 50  0001 C CNN
F 3 "" H 2500 2750 50  0000 C CNN
	1    2500 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 3100 2300 3150
Wire Wire Line
	2300 3150 2700 3150
Wire Wire Line
	2700 3150 2700 3100
Wire Wire Line
	2350 2750 2300 2750
Wire Wire Line
	2300 2750 2300 2800
Wire Wire Line
	2650 2750 2700 2750
Wire Wire Line
	2700 2750 2700 2800
$Comp
L Device:D_ALT D1
U 1 1 5B31703A
P 4450 2750
F 0 "D1" V 4496 2671 50  0000 R CNN
F 1 "1N60" V 4405 2671 50  0000 R CNN
F 2 "cnsit:SMT_DIODE" H 4450 2750 50  0001 C CNN
F 3 "~" H 4450 2750 50  0001 C CNN
	1    4450 2750
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_ALT D2
U 1 1 5B3172B1
P 4450 3150
F 0 "D2" V 4496 3071 50  0000 R CNN
F 1 "1N60" V 4405 3071 50  0000 R CNN
F 2 "cnsit:SMT_DIODE" H 4450 3150 50  0001 C CNN
F 3 "~" H 4450 3150 50  0001 C CNN
	1    4450 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_ALT D3
U 1 1 5B31D911
P 4850 2750
F 0 "D3" V 4804 2829 50  0000 L CNN
F 1 "1N60" V 4895 2829 50  0000 L CNN
F 2 "cnsit:SMT_DIODE" H 4850 2750 50  0001 C CNN
F 3 "~" H 4850 2750 50  0001 C CNN
	1    4850 2750
	0    1    1    0   
$EndComp
$Comp
L Device:D_ALT D4
U 1 1 5B31D918
P 4850 3150
F 0 "D4" V 4800 3450 50  0000 L CNN
F 1 "1N60" V 4900 3450 50  0000 L CNN
F 2 "cnsit:SMT_DIODE" H 4850 3150 50  0001 C CNN
F 3 "~" H 4850 3150 50  0001 C CNN
	1    4850 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2600 4450 2550
Wire Wire Line
	4850 2550 4850 2600
Wire Wire Line
	4450 3300 4450 3350
Wire Wire Line
	4850 3350 4850 3300
Connection ~ 2700 2750
Connection ~ 2700 3150
$Comp
L power:GNDA #PWR03
U 1 1 5B35CF18
P 4050 3000
F 0 "#PWR03" H 4050 2750 50  0001 C CNN
F 1 "GNDA" H 4050 3100 50  0000 C CNN
F 2 "" H 4050 3000 50  0000 C CNN
F 3 "" H 4050 3000 50  0000 C CNN
	1    4050 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3000 4050 2950
Wire Wire Line
	4050 2950 3900 2950
Connection ~ 4850 5700
Wire Wire Line
	4650 4050 5200 4050
Wire Wire Line
	5850 4300 5850 4250
$Comp
L Connector:Conn_Coaxial J1
U 1 1 5B3AB8FE
P 1500 2750
F 0 "J1" H 1400 3000 50  0000 C CNN
F 1 "LO" H 1400 2900 50  0000 C CNN
F 2 "cnsit:SMA_Amphenol_901-144_Vertical" H 1500 2750 50  0001 C CNN
F 3 " ~" H 1500 2750 50  0001 C CNN
	1    1500 2750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1700 2750 1800 2750
Connection ~ 2300 2750
Wire Wire Line
	1500 2950 1500 3150
Wire Wire Line
	1500 3150 2300 3150
Connection ~ 2300 3150
$Comp
L Device:C C2
U 1 1 5B3D0990
P 4450 5450
F 0 "C2" H 4565 5496 50  0000 L CNN
F 1 "0.1u" H 4565 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.29x1.40mm_HandSolder" H 4488 5300 50  0001 C CNN
F 3 "~" H 4450 5450 50  0001 C CNN
	1    4450 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5250 4850 5700
$Comp
L Device:C C1
U 1 1 5B408CE3
P 1950 2750
F 0 "C1" V 1698 2750 50  0000 C CNN
F 1 "0.1u" V 1789 2750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.29x1.40mm_HandSolder" H 1988 2600 50  0001 C CNN
F 3 "~" H 1950 2750 50  0001 C CNN
	1    1950 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 3150 3000 3150
Wire Wire Line
	4450 5250 4450 5300
Wire Wire Line
	5500 4050 5650 4050
$Comp
L Device:C C3
U 1 1 5CFE58D9
P 5350 4050
F 0 "C3" H 5465 4096 50  0000 L CNN
F 1 "0.1u" H 5465 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.29x1.40mm_HandSolder" H 5388 3900 50  0001 C CNN
F 3 "~" H 5350 4050 50  0001 C CNN
	1    5350 4050
	0    1    1    0   
$EndComp
$Comp
L Device:Transformer_1P_2S T1
U 1 1 5C838FE7
P 3400 2950
F 0 "T1" H 3400 3550 50  0000 C CNN
F 1 "T_3743" H 3400 3450 50  0000 C CNN
F 2 "cnsit:T_3743_6" H 3400 2950 50  0001 C CNN
F 3 "~" H 3400 2950 50  0001 C CNN
	1    3400 2950
	1    0    0    -1  
$EndComp
Text Notes 2550 2650 0    50   ~ 0
6dB
$Comp
L power:GNDA #PWR01
U 1 1 5C83A1E6
P 5850 4300
F 0 "#PWR01" H 5850 4050 50  0001 C CNN
F 1 "GNDA" H 6050 4300 50  0000 C CNN
F 2 "" H 5850 4300 50  0000 C CNN
F 3 "" H 5850 4300 50  0000 C CNN
	1    5850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2850 3900 2850
Wire Wire Line
	3900 2850 3900 2950
Wire Wire Line
	3900 3050 3800 3050
Connection ~ 3900 2950
Wire Wire Line
	3900 2950 3900 3050
$Comp
L Device:Transformer_1P_2S T2
U 1 1 5C86D4A6
P 4650 4850
F 0 "T2" V 4700 4350 50  0000 R CNN
F 1 "T_3743" V 4600 4350 50  0000 R CNN
F 2 "cnsit:T_3743_6" H 4650 4850 50  0001 C CNN
F 3 "~" H 4650 4850 50  0001 C CNN
	1    4650 4850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4550 4450 4550 4350
Wire Wire Line
	4550 4350 4650 4350
Wire Wire Line
	4750 4350 4750 4450
Wire Wire Line
	4650 4050 4650 4350
Connection ~ 4650 4350
Wire Wire Line
	4650 4350 4750 4350
Wire Wire Line
	4650 5900 4850 5900
$Comp
L power:GNDA #PWR02
U 1 1 5C88B557
P 2700 3200
F 0 "#PWR02" H 2700 2950 50  0001 C CNN
F 1 "GNDA" H 2850 3150 50  0000 C CNN
F 2 "" H 2700 3200 50  0000 C CNN
F 3 "" H 2700 3200 50  0000 C CNN
	1    2700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3200 2700 3150
$Comp
L power:GNDA #PWR04
U 1 1 5C88CE41
P 4900 5700
F 0 "#PWR04" H 4900 5450 50  0001 C CNN
F 1 "GNDA" H 5050 5650 50  0000 C CNN
F 2 "" H 4900 5700 50  0000 C CNN
F 3 "" H 4900 5700 50  0000 C CNN
	1    4900 5700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 5700 4850 5700
Wire Wire Line
	4850 5700 4850 5900
Wire Wire Line
	4450 5600 4450 5700
Wire Wire Line
	4450 2900 4450 2950
Wire Wire Line
	4850 2900 4850 2950
$Comp
L Device:D_ALT D5
U 1 1 5E62A2D0
P 4450 2400
F 0 "D5" V 4496 2321 50  0000 R CNN
F 1 "1N60" V 4405 2321 50  0000 R CNN
F 2 "cnsit:SMT_DIODE" H 4450 2400 50  0001 C CNN
F 3 "~" H 4450 2400 50  0001 C CNN
	1    4450 2400
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_ALT D6
U 1 1 5E62A2DA
P 4850 2400
F 0 "D6" V 4804 2479 50  0000 L CNN
F 1 "1N60" V 4895 2479 50  0000 L CNN
F 2 "cnsit:SMT_DIODE" H 4850 2400 50  0001 C CNN
F 3 "~" H 4850 2400 50  0001 C CNN
	1    4850 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2250 4450 2200
Wire Wire Line
	4850 2200 4850 2250
$Comp
L Device:D_ALT D7
U 1 1 5E62B75D
P 4450 3500
F 0 "D7" V 4496 3421 50  0000 R CNN
F 1 "1N60" V 4405 3421 50  0000 R CNN
F 2 "cnsit:SMT_DIODE" H 4450 3500 50  0001 C CNN
F 3 "~" H 4450 3500 50  0001 C CNN
	1    4450 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_ALT D8
U 1 1 5E62B767
P 4850 3500
F 0 "D8" V 4800 3800 50  0000 L CNN
F 1 "1N60" V 4900 3800 50  0000 L CNN
F 2 "cnsit:SMT_DIODE" H 4850 3500 50  0001 C CNN
F 3 "~" H 4850 3500 50  0001 C CNN
	1    4850 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 3700 4850 3650
Wire Wire Line
	4450 2200 4850 2200
Wire Wire Line
	3800 2550 3900 2550
Wire Wire Line
	3900 2550 3900 2200
Wire Wire Line
	3900 2200 4450 2200
Connection ~ 4450 2200
Wire Wire Line
	3800 3350 3900 3350
Wire Wire Line
	3900 3350 3900 3700
Wire Wire Line
	3900 3700 4450 3700
Wire Wire Line
	4450 3650 4450 3700
Connection ~ 4450 3700
Wire Wire Line
	4450 3700 4850 3700
Wire Wire Line
	4850 2950 5050 2950
Wire Wire Line
	5050 2950 5050 4450
Connection ~ 4850 2950
Wire Wire Line
	4850 2950 4850 3000
Wire Wire Line
	4250 4450 4250 2950
Wire Wire Line
	4250 2950 4450 2950
Connection ~ 4450 2950
Wire Wire Line
	4450 2950 4450 3000
Wire Wire Line
	2100 2750 2300 2750
Wire Wire Line
	2700 2750 3000 2750
$Comp
L Connector:Conn_Coaxial J2
U 1 1 5B3ABAA0
P 4450 5900
F 0 "J2" H 4350 6050 50  0000 C CNN
F 1 "RF" H 4500 6050 50  0000 C CNN
F 2 "cnsit:SMA_Amphenol_901-144_Vertical" H 4450 5900 50  0001 C CNN
F 3 " ~" H 4450 5900 50  0001 C CNN
	1    4450 5900
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_Coaxial J3
U 1 1 5B3A5F7E
P 5850 4050
F 0 "J3" H 5950 4026 50  0000 L CNN
F 1 "IF" H 5950 3935 50  0000 L CNN
F 2 "cnsit:SMA_Amphenol_901-144_Vertical" H 5850 4050 50  0001 C CNN
F 3 " ~" H 5850 4050 50  0001 C CNN
	1    5850 4050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
