HVAD MANGLER DER

Dette er en start på FSM.
Der mangler stadig:
	1. fra server(testconfig.json) til readable streng.
	2. kommunikation mellem fsm og mqtt client.
	3. små rettelser hist og her.

----------------------------
EVT. KOMMENTAR

Alt kode til testcase er taget fra V2_rocket
Funktionen i testcase kunne måske laves om til en template, for at gøre det mere generisk.(not sure how tho)
Der er stadig generelle tanker i dokumentet som kommentar, så der skal ryddes op senere.
Der er lavet nogle småændringer på div. klasser, for at få det til at spille med vores FSM.
Testcase burde være færdig, der er implementeret forskellige returværdi i forhold til hvad der fejler
-----------------------------
	RETUR VÆRDIER TIL FEJLHÅNDTERING:
		-102 = hvis den fejler med og læse sensordata
		-201 = hvis den fejler med og init pwm
		-204 = hvis den fejler med og starte pwm
		-205 = hvis den fejler emd og stoppe pwm
		-1000 = hvis den ønskede funktion ikke er implementeret endnu
		
-----------------------------
