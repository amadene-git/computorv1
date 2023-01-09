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