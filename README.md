# ARCHIVED
~~This project is long abandoned, and for good reason. I can't bring myself to straight up delete it, so here it is.~~

## Its back!
After a cold long 4 years for Solar Engine being discon, it is now back in production and will be rewritten then released.

## Note
The direction of Solar Engine has change immensely. This iteration, even if it wasn't written as bad as it is, will not be used.
This was my 3rd attempt at any kind of game engine at all. I've had a long time now to get my programming together.

The new engine will support:
  - Dynamic Multiplayer
    When joining other players, their map mods etc will all be replicated to players joining.
    This will allow easily joining your friends who may be using a special playthrough (This only replicates from the server, not vise versa)

  - Luau
    Solar Engine was originally planned to have Lua, we are shifting to Luau.
    It's open sourced, which means not only can I modify the source if ever need be to tailor to the Solar Engine,
    I can reference its internals to understand whats going on on the low end.

    Luau is also well designed with *sandboxing* in mind. Sandboxing is VERY important for anything that replicates then runs on the client.
    It is also very efficient, with not only compiler optimizations in place, it also has runtime optimizations.
    Its typedef features also allow for easily checking and enforcing types during the scripts compile time, rather than needing runtime checks.
    It has many features, but probably the biggest is its collection of LPS, debugging, and benchmarking tools. I'd rather not write these lol.

  - Core Libraries
    The source code for Solar Engine is split into libraries, then used back together to write the engine itself.
    This makes updating the engine much more streamlined for me, which leaves more time to make games with it!
    
  - Task scheduling
    In this iteration of the engine, I didn't do much well in regards towards event handling. Just another big hardwritten loop.
    As of writing this, I've already completed a much more advanced, expandable, and powerful task scheduling library.
    It took me 3-4 months of researching and planning, and 5 hours and 44 minutes to completely rewrite; not because of its size but rather its complexity.

Unfortionately, unlike this iteration of Solar Engine, I will NOT be open sourcing the new overhaul in the foreseeable future.
This is for a many of reasons, but the most obvious is: It's new.
I've spent a LONG time working on not only this previous iteration of the engine, but between its last update and now there's been alot of work behind the scenes.
The last thing I want is someone with a big tik tok following using the engine to write a game, and my games never get attention. I need to make a living too.

Well, if you want to keep updated for when this is coming out, or get previews towards its features, join https://discord.gg/yYUcZ6gf
Theres no ETA, as it is very early in its development. Barebone even, but the future is going to be a bright one.
