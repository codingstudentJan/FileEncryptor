# FileEncryptor

A minimal, security-focused command-line tool written in modern C++ for encrypting and decrypting files using **well-established cryptographic primitives**.

This project is intentionally built with a strong emphasis on **correctness, safe defaults, and clean design**, rather than experimental or custom cryptography.

---

## Current Status

 **Early development – functional encryption implemented**

At this stage, FileEncryptor provides:

- A working **CLI interface**
- File **encryption using authenticated encryption**
- Secure **passphrase-based key derivation**
- Deterministic and reproducible builds
- Clean project structure (CMake-based)

Encryption already works end-to-end and produces encrypted output files.  
Decryption and format validation are currently being finalized.

---

## What It Can Do (Today)

- Encrypt files via command line
- Derive encryption keys securely from a passphrase
- Use modern, vetted cryptographic libraries (no custom crypto)
- Fail safely on invalid input or usage
- Build cleanly without embedding secrets in the repository

---

## Planned Features

The following features are explicitly planned and tracked:

### Core Functionality
- File **decryption** with authentication verification
- Clear and versioned **file format** (magic bytes, header, metadata)
- Detection of tampering or incorrect passphrases
- Streaming encryption/decryption for large files

### Security & Usability
- Memory-safe handling of sensitive data
- Constant-time operations where applicable
- Optional passphrase input via prompt or environment variables
- Explicit and documented cryptographic parameters

### Engineering Quality
- Automated tests (round-trip, negative cases, corruption detection)
- Clear threat model and security assumptions
- Robust error handling and exit codes
- Cross-platform support (Linux / Windows)

---

## Non-Goals

To be explicit, this project will **not**:

- Implement custom cryptographic algorithms
- Compete with full-disk encryption tools
- Provide GUI functionality
- Act as a key management system

FileEncryptor is a **learning-oriented but production-quality** security engineering project, not a consumer product.

---

## Build (Preview)

```bash
mkdir build
cd build
cmake ..
cmake --build .
