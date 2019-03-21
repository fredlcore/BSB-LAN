# Translate BSB-LAN into your language! #

Translating BSB-LAN into your language is easy, and you don't have to do all at once (or at all) - simply start with the web interface labels or the category names first and then you or others can follow up later, whenever time allows it.

**How to do it?**
- Identify your language file. Naming follows the system "LANG_" + 2-letter ISO-Code of your country + ".h".  
If your language does not have a file yet, you can simply create one yourself. 
- Pick one of the existing language files (German is of course 100% complete, English only 5%, but at least it has a bit more than the other languages) that you are most comfortable with to translate from.
- Copy line by line that you want to translate into your LANG_XX.h file.
- Translate what’s inside the quotation marks. Make sure that the translation is always enclosed in quotation marks, otherwise compilation will unfortunately fail with error messages that won’t point to the language files. Do not in any change anything that is outside the quotation marks.
- Once you have completed / paused translation and want to test it, set #define LANG in BSB_lan_config.h to your (new) country
code. If possible, try to run ./create-undefs.pl (if you have a Perl interpreter) before compilation. It’s not necessary, but prevents compiler warnings. Check if the translations are how you want them to be.
- Once you are done, you can send me a pull request or simply send the file via e-mail, whatever is easier for you.

**Thank you!**
