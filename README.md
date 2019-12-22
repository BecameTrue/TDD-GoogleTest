# TDD-GoogleTest

On this project, I study **TDD**(Test Driven Development).

## About TDD

From [Wikipedia](https://en.wikipedia.org/wiki/Test-driven_development), the free encyclopedia.

**Test-driven development**(TDD) is a **software development process** that relies on the repetition of a very short development cycle: **requirements are turned into very specific test cases**, then the software is **improved so that the tests pass**. This is opposed to software development that allows software to be added that is not proven to meet requirements.

American software engineer Kent Beck, who is credited with having developed or "rediscovered" the technique, stated in 2003 that TDD encourages **simple designs and inspires confidence**.

...

---

## Modern C Programming With Test Driven Development

I studied with a book, **"Modern C Programming With Test Driven Development"**.

### Cycle

1. Write a small test. 
2. Ensure it fails. 
3. Get it to pass. 
4. Review and clean up the design including that of the tests.
5. Ensure the tests all still pass.

A common **misconception** of TDD is that you first define all the tests before building an implementation. Instead, you focus on **one test at a time** and incrementally consider the next behavior to drive into the system from there.

Each test you write in TDD and get to pass represents a new, working piece of behavior that you add to the system. Aside from getting an entire feature shipped, your **passing** tests represent your **best measure of progress**. You **name** each test to describe the **small piece of behavior**.

The failing test prods us to write code, **no more than necessary to pass** the assertion.

**Incrementalism** is at the heart of what makes TDD successful. An incremental approach will seem quite unnatural and slow at first. However, taking small steps will increase your speed over time, partly because you will avoid errors that arise from taking large, complicated steps.

Let’s work through an example and test-drive a class named SQL whose job is to generate SQL statements (select, insert, delete, and so on) given database metadata about a table.

We seek meaningful behavior with each new test. That means we don’t directly test-drive getters, setters, or constructors. **They’ll get coded as needed when driving in useful behaviors.** Generating a SQL statement that operates on a table seems useful and small enough. We can choose from drop table or truncate table.

---

### Google Mock

**Google Mock** lets us define a fixture class in which we can declare functions and member data for a related set of tests. Technically, all Google Mock tests use a fixture that it generates behind the scenes. Google Mock instantiates the fixture class once per test.

However, the implementation that we seek is one that generalizes our solution —_but does not over-generalize it to support additional concerns_— and doesn’t introduce code that duplicates concepts already coded.

In Google Mock, prepending `DISABLED_` to the test name tells Google Mock to skip executing it.

```cpp
TEST_F(SoundexEncoding, DISABLED_ReplacesMultipleConsonantsWithDigits) {
    ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}
```

---

### Unit Test and TDD Fundamentals

**TDD results in unit tests.** A unit test **verifies the behavior** of a code unit, where a unit is the **smallest testable piece** of an application.

#### Unit Test Organization and Execution

A single unit test consists of a **descriptive name** and **a series of code statements**, conceptually divided into **four** (ordered) parts.

1. (Optional) statements that **set up a context** for execution
2. One or more statements to **invoke the behavior** you want to verify
3. One or more statements to **verify the expected outcome**
4. (Optional) **cleanup** statements (for example, to release allocated memory)

Some folks refer to the first three parts as **Given-When-Then**. In other words, Given a context, When the test executes some code, Then some behavior is verified.

The goal of “burning the TDD cycle in your brain” is to make you **comfortable with writing tests** first to specify behavior and with cleaning up code each time through the cycle. Ingraining this habit will **free your mind to instead think about the more challenging problem of growing a solution incrementally.**

#### At each point in the TDD cycle, you must be able to answer many questions.

- Write a small test. **What’s the smallest possible piece of behavior** you can increment the system by? Does the system already have that behavior? How can you concisely describe the behavior in the **test’s name**? Does the interface expressed in the test represent the **best possible way** for client code to use the behavior?
- **Ensure the new test fails. If it doesn’t, why not?** Does the behavior already exist? Did you forget to compile? Did you take too large a step in the prior test? Is its assertion valid?
- Write the code you think makes the test pass. Are you writing **no more code than needed** to meet the current set of behaviors specified by the tests? Are you recognizing where the code you just wrote will need to be cleaned up? Are you following your team’s standards? 
- Ensure all the tests pass. If not, did you code things incorrectly, or **is your specification incorrect?** 
- Clean up the code changes you just made. What do you need to do in order to get your code to follow team standards? Does your new code duplicate other code in the system that you should clean up, too? Does the code exhibit questionable smells? Are you **following good design principles?** What else do you know about design and clean code that you should apply here? Otherwise, is the design evolving in a good direction? Does your code change impact the design of other code areas that you should also change?
- Ensure the tests all still pass. **Do you trust that you have adequate unit test coverage?** Should you run a slower set of tests to have the confidence to move on? **What’s the next test?**

#### Mind-Sets for Successful Adoption of TDD

TDD is a discipline to help you **grow a quality design**, not just a haphazard approach to verifying pieces of a system. Success with TDD derives from adopting a proper mentality about how to approach it.

##### Incrementalism

Every time you add a new unit of behavior into the system, you **know it all still works**—you wrote a test for the new behavior, and you have tests for every other unit already built.

##### Using Tests to Describe Behavior

Good tests will save time by **acting as a trustworthy body of comprehensive documentation** on the behaviors your system exhibits.

##### Keeping It Simple

Code that is readable, code that doesn’t exhibit duplication, and code that eschews other unnecessary complexities. These characteristics **maximally reduce your maintenance costs.**

---

### Testing

#### Fixture

Related tests need to run in the same environment. You’ll have many tests that require **common** initialization or helper functions. Many test tools let you define a **fixture**—a class that provides support for cross-test reuse.

Following code shows defining a fixture class.

```cpp
using namespace ::testing;

class ARetweetCollection: public Test {
public:
    RetweetCollection collection;
};
```

To give a test **access to members** defined in the **fixture** class, you must change the TEST macro definition to **TEST_F** (the trailing F stands for fixture).

Like this :

```cpp
TEST_F(ARetweetCollection, IsEmptyWhenCreated) {
    ASSERT_THAT(collection.isEmpty(), Eq(true));
}
```

#### SetUp & TearDown function

If all of the tests in a test case require one or more statements of **common initialization**, you can move that code into a **setup function** that you define in the fixture. In _Google Mock_, you must name this member function **SetUp** (it overrides a virtual function in the base class ::testing::Test).

After creating the fixture instance, Google Mock executes the code in SetUp() and then executes the test itself.

The **teardown function** is essentially the **opposite** of the setup function. It executes after each test, even if the test threw an exception. You use the teardown function for **cleanup purposes**—to release memory (as in this example), to relinquish expensive resources (for example, database connections), or to clean up other bits of state, such as data stored in static variables.

#### Run a subset of tests

Google Mock makes it easy to run a subset of the tests by specifying what is known as a **test filter**. You specify a test filter as a **command-line argument** to your test executable. The filter allows you to specify tests to execute in the form `test_case_name.test_name`

For example :

```bash
~$ ./test --gtest_filter=ATweet.* # slightly less weak
```

#### Becareful on comparing floats

Floating-point numbers are **imprecise binary representations** of real numbers. As such, the result of a float-based calculation **might not exactly match** another float value, even though it appears as if they should. 

Here’s an example: 

```cpp
double x{4.0};
double y{0.56};
ASSERT_THAT(x + y, Eq(4.56));
```

On book, received the following failure when writer executed the previous assertion:

```bash
Value of: x + y
Expected: is equal to 4.56
Actual: 4.56 (of type double)
```

...

#### Test-driving challenge

When external dependency is needed, for instance invoking a REST service.

- Making an actual HTTP call to invoke a REST service is very slow and will bog down your test run.
- The service might not always be available.
- You can’t guarantee what results the call will return.

To avoid being blocked, here comes the **Test Double**.

#### Test Double

You can avoid being blocked, in any of these cases, by employing a test double. HTTP giving you trouble? Create a test double HTTP implementation! The job of the test double will be to support the needs of the test. When a client sends a GET request to the HTTP object, the test double can return a canned response.

There are two ways to create a test double implementation.

1. Make stub by your hand.
2. Use **Google Mock**.

**Google Mock** is to create a derived class that declares mock methods.

---

## Google Mock Docs

1. [README](https://github.com/google/googletest/blob/master/googlemock/README.md)
2. [CheatSheet](https://github.com/google/googletest/blob/master/googlemock/docs/cheat_sheet.md)
3. [Cook Book](https://github.com/google/googletest/blob/master/googlemock/docs/cook_book.md)
4. [For Dummies](https://github.com/google/googletest/blob/master/googlemock/docs/for_dummies.md)
5. [GMock FAQ](https://github.com/google/googletest/blob/master/googlemock/docs/gmock_faq.md)
6. [Pump Manual](https://github.com/google/googletest/blob/master/googlemock/docs/pump_manual.md)

---

## Practice

### What to build?

**Roman Numeral Converter**

Takes an arabic number and returns its Roman numeral equivalent as a string.

### Remind of the cycle

1. Write a small test. 
2. Ensure it fails. 
3. Get it to pass. 
4. Review and clean up the design including that of the tests.
5. Ensure the tests all still pass.

### Roman Numerals

[From Wiki](https://en.wikipedia.org/wiki/Roman_numerals)

|Symbol| I | V | X | L | C | D |  M  |
|------|---|---|---|---|---|---|-----|
|Value | 1 | 5 |10 |50 |100|500|1,000|

There is not, and never has been, an "official", "binding", or universally accepted standard for Roman numerals. Usage in ancient Rome varied greatly and remained somewhat inconsistent in medieval times and later. The "rules" of the system as it is now applied have been established only by general usage over the centuries.

#### "Standard" forms

Roman numerals are essentially a decimal or "base 10" number system, in that the powers of ten – thousands, hundreds, tens and units – are written separately, from left to right, in that order. In the absence of "place keeping" zeros, different symbols are used for each power of ten, but a common pattern is used for each of them.

The underlying form of this pattern employs the symbols I and V (representing 1 and 5) as simple tally marks, to build the numbers from 1 to 9. Each marker for 1 (I) adds a unit value up to 5 (V), and is then added to (V) to make the numbers from 6 to 9. Finally the unit symbol for the next power completes a "finger count" sequence:

**I, II, III, IIII, V, VI, VII, VIII, VIIII, X.**

At some early time the Romans started to use the shorter forms IV ("one less than 5") for IIII, and IX ("one less than 10") for VIIII – a convention that has been widely, although not universally, used ever since. This convention is called "subtractive" notation, as opposed to the "additive" notation of IIII and VIIII. Thus the numbers from 1 to 10 are generally written as:

**I, II, III, IV, V, VI, VII, VIII, IX, X.**

The multiples of 10, from 10 to 100, are written according to the same pattern, with X, L, and C taking the place of I, V, and X

**X, XX, XXX, XL, L, LX, LXX, LXXX, XC, C.**

Note that 40 is usually written XL ("10 less than 50") rather than XXXX, and 90 as XC ("10 less than 100") rather than LXXXX: following the same "subtractive" pattern as IV and IX.

### Things to test

- [x] Can handle invalid input? (less than zero, zero, real number, alphabet, ...)
- [x] Can convert valid input?

### Testing History

#### Can handle invalid input?

Code:

```cpp
#include <romanNumeralConverter.h>
#include <string>

using namespace std;

string RomanNumeralConverter::get(int input) {
    if(input <= 0) return "INVALID";
}
```

```cpp
#include <gmock/gmock.h>
#include <romanNumeralConverterTest.h>

using namespace testing;

TEST_F(RomanNumeralConverterFixture, CanHandleInvalidInput) {
    ASSERT_EQ(converter.get(-123), "INVALID");
    ASSERT_EQ(converter.get(0), "INVALID");
}
```

Result:

```bash
~$ ./test/test-tdd-googletest
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from RomanNumeralConverterFixture
[ RUN      ] RomanNumeralConverterFixture.CanHandleInvalidInput
[       OK ] RomanNumeralConverterFixture.CanHandleInvalidInput (0 ms)
[----------] 1 test from RomanNumeralConverterFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

#### Can convert valid input?

Firstly I typed a failing test, which expects for "I" when "1" is given as an input.

Code:

```cpp
TEST_F(RomanNumeralConverterFixture, CanConvertValidInput) {
    ASSERT_EQ(converter.get(1), "I");
}
```

Result:

```bash
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from RomanNumeralConverterFixture
[ RUN      ] RomanNumeralConverterFixture.CanHandleInvalidInput
[       OK ] RomanNumeralConverterFixture.CanHandleInvalidInput (0 ms)
[ RUN      ] RomanNumeralConverterFixture.CanConvertValidInput
Segmentation fault
```

Seems like it passed the test, but there was an **Segmentation fault**.

Of course, currently the `string RomanNumeralConverter::get(int input)` only returns something when input <= 0. So now, let's make this to pass the test.

Code:

```cpp
string RomanNumeralConverter::get(int input) {
    if(input <= 0) return "INVALID";

    return "I";
}
```

Result: 

```bash
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from RomanNumeralConverterFixture
[ RUN      ] RomanNumeralConverterFixture.CanHandleInvalidInput
[       OK ] RomanNumeralConverterFixture.CanHandleInvalidInput (0 ms)
[ RUN      ] RomanNumeralConverterFixture.CanConvertValidInput
[       OK ] RomanNumeralConverterFixture.CanConvertValidInput (0 ms)
[----------] 2 tests from RomanNumeralConverterFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
```

Before to generate several more tests, these are the check-list of **_Can convert valid input?_**

- [x] converts 1 to "I" 
- [ ] converts 3 to "III"
- [ ] converts 5 to "V"
- [ ] converts 8 to "VIII"
- [ ] converts 10 to "X"
- [ ] converts 12 to "XII"
- [ ] converts 15 to "XV"
- [ ] converts 18 to "XVIII"
- [ ] converts 20 to "XX"

After passing all the tests,

- [x] converts 1 to "I" 
- [x] converts 3 to "III"
- [x] converts 5 to "V"
- [x] converts 8 to "VIII"
- [x] converts 10 to "X"
- [x] converts 12 to "XII"
- [x] converts 15 to "XV"
- [x] converts 18 to "XVIII"
- [x] converts 20 to "XX"

Main function & result : 

```cpp
int main(void) {
    RomanNumeralConverter converter;

    cout << "[YEAR] " << converter.get(2019) << endl;
    cout << "[MONTH] " << converter.get(12) << endl;
    cout << "[DAY] " << converter.get(22) << endl;
}
```

```bash
[YEAR] MMXVIIII
[MONTH] XII
[DAY] XXII
```

See rest of the code at [Github](https://github.com/BecameTrue/TDD-GoogleTest).