<style>
.smallcaps { font-variant: small-caps; }
</style>

# Dokumentace k 2. projektu IPK – IPK25 Chat

**Autor:** Jan Kalina (`xkalinj00`)

**Předmět:** *IPK – Počítačové komunikace a sítě* <br>
**Akademický rok:** *2024/2025*

---

## Obsah

## 1. Úvod

---

## 2. Teoretický základ a účel aplikace

---

## 3. Sestavení a spuštění programu

### 3.1 Sestavení programu pomocí `Makefile`

### 3.2 Spuštění programu

---

## 4. Přehled architektury a struktura projektu

---

## 5. Testování a verifikace funkčnosti

### 5.1 Testování funkčnosti skenování

#### 5.1.2 Testovací scénáře

### 5.2 Jednotkové testy pomocí frameworku Google Test

#### 5.2.1 Testovací prostředí

#### 5.2.2 Co bylo testováno?

#### 5.2.3 Proč to bylo testováno?

#### 5.2.4 Jak to bylo testováno?

---

## 6. Závěr

---

## 7. Bibliografie

---

## 8. Přílohy

### 8.1 Adresářový strom projektu

### 8.2 Výstup příkazu `make help`

```bash
make help
```

<pre>
<span style="color: #ffcc00;">Main Commands:</span>
<span style="color: #00cccc;">all                           </span> Builds the 'ipk25-chat'
<span style="color: #00cccc;">build                         </span> Builds the 'ipk25-chat' via CMake in developer version and Make in submission version
<span style="color: #00cccc;">clean                         </span> Runs 'clean-all' in developer / submission mode (different versions)
<span style="color: #00cccc;">debug                         </span> Builds the application in debug mode with more strict warnings
<span style="color: #00cccc;">doc                           </span> Generates project documentation into the `doc` directory (different versions)
<span style="color: #00cccc;">help                          </span> Prints help for using the Makefile
<span style="color: #00cccc;">pack                          </span> Creates a ZIP archive with files intended for submission (not allowed for submission)
<span style="color: #00cccc;">run                           </span> Runs the executable 'ipk25-chat' with print help argument
<span style="color: #00cccc;">test                          </span> Builds and runs the test executable 'ipk25-chat-test' (not allowed for submission)

<span style="color: #ffcc00;">Clean (special):</span>
<span style="color: #00cccc;">clean-all                     </span> Removes all created files (build, doc, executable, archive, ...)
<span style="color: #00cccc;">clean-build                   </span> Removes the 'build' directory
<span style="color: #00cccc;">clean-debug-exec              </span> Removes the debug executable
<span style="color: #00cccc;">clean-doc                     </span> Removes generated content of the 'doc' directory
<span style="color: #00cccc;">clean-exec                    </span> Removes the executable
<span style="color: #00cccc;">clean-pack                    </span> Removes the 'pack' directory including the archive (not allowed for submission)
<span style="color: #00cccc;">clean-test                    </span> Removes 'test/bin' folder with test executables

<span style="color: #ffcc00;">Test:</span>

<span style="color: #ffcc00;">Pack (special):</span>
<span style="color: #00cccc;">pack-prepare                  </span> Copies all necessary files to the 'pack/xkalinj00' directory (not allowed for submission)

<span style="color: #ffcc00;">Install Dependencies:</span>
<span style="color: #00cccc;">install-dev-dep               </span> Installs dependencies needed for using all 'Makefile' functions (not allowed for submission)
<span style="color: #00cccc;">install-doc-dep               </span> Installs dependencies needed for generating documentation (not allowed for submission)
<span style="color: #00cccc;">install-help-dep              </span> Installs dependencies needed for printing 'Makefile' help (not allowed for submission)
<span style="color: #00cccc;">install-pack-dep              </span> Installs dependencies needed for project packaging (not allowed for submission)
<span style="color: #00cccc;">update-dep                    </span> Updates the list of available packages (not allowed for submission)
</pre>

#### 8.3 Výsledky unit testů
