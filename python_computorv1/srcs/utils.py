INTEGER = 'INTEGER'
PLUS    = 'PLUS'
MINUS   = 'MINUS'
MUL     = 'MUL'
DIV     = 'DIV'
EOF     = 'EOF'
LPAR    = '('
RPAR    = ')'
X       = 'X'
POWER	= 'POWER'
EQUAL	= 'EQUAL'
POINT	= '.'


from srcs.Number import Number

NUMBERNULL = Number(0) # constant null

def my_sqrt(num, root = Number(2), n_dec = 20):
    nat_num = Number(1)
    while nat_num**root <= num:
        result = nat_num
        nat_num += Number(1)

    for d in range(1, n_dec+1):
        increment = Number(10)**Number(-d)
        count = Number(1)
        before = result

        while (before + increment*count)**root <= num:
            result = before + increment*count
            count += Number(1)
    return result



def preparse(text):
    i = 0
    n = len(text)

    while i < n:
        if text[i] in ('x', 'X'):
            if i != 0 and text[i - 1].isdigit():
                text = text[:i] + " * x" + text[i+1:]
        n = len(text)
        i += 1
    return text



import signal
from contextlib import contextmanager
from time import sleep

@contextmanager
def timeout(time):
    # Register a function to raise a TimeoutError on the signal.
    signal.signal(signal.SIGALRM, raise_timeout)
    # Schedule the signal to be sent after ``time``.
    signal.alarm(time)

    try:
        yield
    except TimeoutError:
        pass
    finally:
        # Unregister the signal so it won't be triggered
        # if the timeout is not reached.
        signal.signal(signal.SIGALRM, signal.SIG_IGN)


def raise_timeout(signum, frame):
    raise TimeoutError


def my_func():
    # Add a timeout block.
    with timeout(10000000):
        print('entering block')
        sleep(1)
        print('This should never get printed because the line before timed out')


