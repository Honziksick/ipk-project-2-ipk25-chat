# CHANGELOG

**Autor:** Jan Kalina (`xkalinj00`)

**Předmět:** *IPK – Počítačové komunikace a sítě* <br>
**Akademický rok:** *2024/2025* <br>
**Projekt:** *2. projekt IPK – IPK25 Chat Client*

---

## Implementovaná funkcionalita

- Podpora dvou transportních protokolů **TCP** a **UDP** pro komunikaci se serverem.
- Implementace vlastního mechanismu spolehlivého přenosu dat pro **UDP** variantu, včetně retransmisí, potvrzování zpráv a deduplikace zpráv.
- Silně modulární objektově orientovaná architektura s využitím návrhových vzorů, dědičnosti a polymorfismu, využití rozhraní a bázových tříd pro deduplikaci kódu.
- Využití pokročilých **C++** technik jako je práce se sdílenými a unikátními ukazateli, implementace univerzálních šablonových funkcí, robustní správa výjimek a dalších 
užitečných a efektivních praktik přednášených v předmětu *Seminář C++*.
- Textové uživatelské rozhraní pro zadávání zpráv a příkazů s plnou podporou příkazů `/auth`, `/join`, `/rename`, `/bye` a `/help`.
- Robustní parsování uživatelských vstupů a validace zpráv včetně kontroly jejich formátu a délky.
- Efektivní řízení komunikace pomocí stavového automatu (*FSM*) pro oba typy protokolů.
- Korektní zpracování dynamických portů u **UDP** komunikace.
- Podpora bufferování zpráv a zpracování fragmentovaných zpráv, podpora situací s více zprávami v jednom paketu.
- *Graceful termination* při ukončení komunikace a odchodu ze serveru a správná reakce na příchozí zprávu `BYE`.
- Implementace mechanismu _keep-alive_ reagující na zprávy typu `PING` od serveru přímo v modulu starající se o síťovou komunikaci.
- Komplexní systém zpracování výjimek pro korektní ukončení při různých typech chyb.
- Argumenty příkazové řádky jsou plně nepoziční a byly přidány i jejich dlouhé varianty.
- Přátelská uživatelská nápověda přátelská chybová hlášení, která často obsahují také informace o tom, jak bude klient reagovat nebo odkaz na výpis nápovědy.
- Kontrola timeout limitu na příjem `REPLY` zprávy od serveru implementována přímo v rámci *FSM*.
- U varianty **UDP** je součástí *FSM* také buffer uživatelských příkazů, aby uživatel nemusel při nedokončené síťové komunikaci čekat na možnost zadání dalšího příkazu.
- ...

## Známá omezení

- Chatovací klient podporuje pouze spojení přes **IPv4**.
- Délka zpráv a parametrů a povolené znaky jsou omezeny protokolem **IPK25-CHAT**.

V současné době nejsou známa žádná další omezení nebo problémy. Aplikace byla důkladně testována v popsaném testovacím 
prostředí a během testování nebyla objevena žádná další kritická omezení.
