# cv_tricks

## Setup

Install venv

```bash
python3 -m venv .venv
```

Install conan (in venv)

```bash
pip install conan
```

Install requirements. Might have to install packages for 
```bash
conan install . --update --build=missing
```


Build project

```bash
conan build .
```