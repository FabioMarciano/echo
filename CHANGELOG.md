# Changelog

All notable changes to the **Echo**'s project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Windows support
  - DLL / LIB
  - resource.rc file


## 0.0.1 - 2018-11-14

### Added

- This **CHANGELOG** file.

### Changed

- The Echo's anonymous main structure to a named (`__echo__`) structure.

### Fixed

- The value of `__EOF__` constant was not defined if __cplusplus was defined.
- The `__echo__` variable 'defined but not used -Wunused-variable'.
