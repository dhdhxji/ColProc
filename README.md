# Clocky
## Usage
### Install dependencies
- [esp-idf framework](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#installation-step-by-step)
- libclang (installation depends on Your pkg manager, `apt install libclang` for Ubuntu)
- python3 with libclang bindings 
    ```
    pip3 install clang
    ```
### Build the project and flash firmware
```
idf.py build flash 
```