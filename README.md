# Celeris 🚀

**Celeris** is a lightweight, high-performance web server written in modern C++. It allows developers to spin up custom HTTP servers using a simple, HTML-like configuration system. Celeris is designed for speed, flexibility, and ease of use — whether you're building APIs, serving static files, or experimenting with new ideas.

---

## ✨ Features

- ⚡ **Fast and Lightweight** – Built in C++ for maximum performance.
- 🧱 **Custom Configuration** – Define your server behavior using intuitive HTML-like syntax.
- 🔁 **Routing** – Easily create and manage routes.
- 🔐 **Authentication Support** – Secure endpoints with built-in auth mechanisms.
- 📁 **Static File Serving** – Serve HTML, CSS, JS, and media files.
- 🧵 **Multithreading** – Handles concurrent requests efficiently (in development).
- 🛠️ **Extensible** – Built to support plugins and middleware in the future.

---

## 📦 Installation

> Coming soon: Install via `.exe` installer, package manager, or source.

For now, clone and build manually:

```bash
git clone https://github.com/amethystcoder/Web-Serve.git
cd Web-Serve
make   # or cmake . && make
./Web-Served
```

---

## ⚙️ Configuration

Celeris uses a lightweight markup-style config file:

```html
<server port="8080">
  <route path="/hello">
    <response>Hello, world!</response>
  </route>
</server>
```

More details and examples coming soon.

---

## 📂 Project Structure

```bash
celerisd/            # Core source code
configs/             # Sample server config files
public/              # Static assets (optional)
docs/                # Documentation (in progress)
tests/               # Unit and integration tests
```

---

## 🧪 Running Tests

```bash
make test
# or
./run_tests
```

---

## 🚧 Roadmap

- [x] Basic routing and static server
- [x] HTML-like configuration parsing
- [ ] Request handling concurrency
- [ ] Middleware support
- [ ] Plugin system
- [ ] HTTPS support
- [ ] WebSocket integration

---

## 🤝 Contributing

Contributions are welcome! Please open an issue or PR.

1. Fork the repo
2. Create your feature branch (`git checkout -b feature/foo`)
3. Commit your changes (`git commit -am 'Add foo'`)
4. Push to the branch (`git push origin feature/foo`)
5. Open a pull request

---

## 📄 License

MIT License. See `LICENSE` file for details.

---

## 🙌 Acknowledgments

Developed with ❤️ by [Joshua Collins](https://github.com/amethystcoder).
