# Echo (Ηχώ)

> Juno had made her talk this way, because,  
> when she could have caught out those mountain nymphs  
> lying beside her husband Jupiter,  
> **Echo** would deliberately detain her  
> with a long chat, until the nymphs had fled.  
> After the goddess realized the trick,  
> she said:  
> "That tongue of yours has swindled me.  
> I will give you less power over it,  
> the very briefest use of your own voice."
>
> *-- **Ovid (Publius Ovidius Naso)** - Metamorphoses, Book III, 556 - 565*
___
# Version

See the **version** file at project's folder.
___
# Description

**Echo** is a simple log library. Easy to use and very flexible.

The library enables developers to log messages on stdout/stderr, and (or) redirects these outputs to custom files.
___
# Installation

  * Download or clone the source code from the repository
  * Go to the **Echo** project's folder
  ``` shell
  $ cd echo/
  ```
  * Type `make` to build the library
  ``` shell
  $ make
  ```
The command above creates the *bin* folder and the following files:

  * A static library named **libecho.a**
  * A shared library named **libecho.so.1.0.0** <sup>1</sup>
  * A symbolic link named **libecho.so.1** <sup>1</sup> pointing to **libecho.so.1.0.0** <sup>1</sup>
  * A symbolic link named **libecho.so** pointing to **libecho.so.1** <sup>1</sup>

(1) Considering the version value 1.0.0:
___
For more details about the use of static and shared libraries, please refer to the project's wiki.
___
# Usage

There are several manners of how to use the **Echo** library, please refer to the project's wiki to learn all about it.
___
# Todo

  * Windows support
    * DLL / LIB support
    * Add resource.rc file
  * Refactoring
___
# License

See the **LICENSE** file at root of this project.
