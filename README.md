# ecraft

`ecraft` is an open source programming library, managed by [Junior Ohanyere](https://github.com/juniorohanyere), and distributed under the [`GPL-3.0 license`](LICENSE) terms and conditions. It is designed to enable programmers with knowledge in any programming language to create and build `electronic crafts` like stories, short-stories, comics, novels, novella, letters, essays, musics, etc, by writing codes. It aims to bring craft into programming

Welcome to the era of programming these craft with your favourite programming language as an electronic craft

# expected features

- story writing (short stories, novels, etc)
- comics
- letter writing
- speech
- text to speech (tts) & speech to text
- essay writing
- drawing and painting
- video & photo making and manipulation
- export as(.pdf, .txt, .doc, .png, long image, etc)
- share your craft to anyone in form of executables or any document format of your choice
- command line interface (cli)
- graphical user interface (gui)
- support on multipl operating systems
- support on multiple programming languages (Python, C, Rust, Java, etc)
- much more to come...

# current features

the ecraft library is currently under construction with `not much to try features`
## programming languages currently supported on

- **C**: under construction

# try the demo

the **ecraft** library has dependencies, make sure to install the dependencies first
**on debian based systems:**
```bash
sudo apt-get install libncurses6-dev libtermbox-dev gawk
```

**after installing all necessary dependencies, run:**
```bash
make
```
**this generates two library files:** `libecraft.so` and `libecraft.a`

**to dynamically test the demo, run:**
```bash
make test	# based on libecraft.so
```

**to statically test the demo, run:**
```bash
make test-static	# based on libecraft.a
```

https://github.com/juniorohanyere/ecraft/assets/106378800/41942191-8149-493c-92c6-2c8f3819df0a
