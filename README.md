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

#### Check for..

With a testing mentality, you seek to create tests that cover a breadth of concerns. You create tests for five types of cases: **zero, one, many, boundary, and exceptional cases.**

---

5 챕터 부터 각 챕터 별 중요 이론 뽑아내기

부록의 Roman Numeral Converter 만들고 과정 기록하기