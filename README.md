# python_code_injection
This program compiles to a DLL and allows you to execute python code upon injection if the python interpreter is persistent.

After you have compiled it, you can now use an injector [like this](https://github.com/gumbobr0t/dll-injector) to embed the DLL into the pyinstaller executable.

As in the directory of where the script file your injecting to lies, the DLL will try to find `injection.txt` containing plain python code which is then executed in a seperate thread, but with the python interpreter inside the proc you injected to.
