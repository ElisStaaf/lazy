# Lazy
Lazy is basically STDI. While that may sound like some horrid disease, look
at this data I found from a totally-not-sketchy-at-all-website:
```
===== Most Common "STDI" Abbreveations =====

- Short-Term Disability Insurance
- Occupational Health, Workplace, Medical
- Synthetic Training Device Instructor
- Science and Technology Diplomacy Initiative
- Information, Technology, Computer
- Sekolah Tinggi Desain Indonesia
- Small Town Design Initiative
- Small Towns Development Initiative
- Southwest Technology Development Institute
- Stereo Tube Direct Interface
- Systolic Time Diameter Index
```
But at the very bottom of the list I have added a new one: `[C] STDlib Improved`!

## History
So this thing started back in the 1800s when I was figuring out C for the first time,
I was frustrated, as C had a minimal standard library. Take that as you will, nowadays
I quite like the C standard library but back then I despised it, I wanted to create something
that you could just *use*, like this:
```c
#include <magical-library-with-solutions-to-everything.h>

int main() {
    try()
        println("Hello World!");
    catch()
        println("NO YOU STUPID IDIOT");
        return 1;
    return 0;
}
```
Basically, a heaven where everything becomes easier, a world were *this*:
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdshit.h>
#include <aids.h>
```
Becomes *this*:
```c
#include <magical-library-with-solutions-to-everything.h> /* Maybe I should
                                                           * come up with a
                                                           * better name? */
```
And thus, `lazy(.h)` was born!

## Example
```c
#include <lazy.h>
#include <errno.h>
#include <assert.h>

int main(int argc, char **argv) {
    errno = 0;
    try {
        print("Hello World!");
    } catch(EDOM) {
        assert(errno = EDOM);
    }
    return 0;
}
```

## Install
```sh
git clone https://github.com/ElisStaaf/lazy
cd lazy
sudo ./install.sh
echo "Enjoy!"
```
