import click

@click.command()
@click.option('--count', default=1, help='Number of greetings.')
@click.option('--name', prompt='Your name',
              help='The person to greet.')
def hello(count, name):
    """Simple program that greets NAME for a total of COUNT times."""
    for x in range(count):
        click.echo('Hello %s!' % name)

if __name__ == '__main__':
    hello()
    
    
"""
>C:\Python37\python.exe hello.py --help
Usage: hello.py [OPTIONS]

  Simple program that greets NAME for a total of COUNT times.

Options:
  --count INTEGER  Number of greetings.
  --name TEXT      The person to greet.
  --help           Show this message and exit.
  
>C:\Python37\python.exe hello.py
Your name: weifeng
Hello weifeng!

>C:\Python37\python.exe hello.py --count=3
Your name: weifeng
Hello weifeng!
Hello weifeng!
Hello weifeng!

>C:\Python37\python.exe hello.py --count=3 --name=weifeng
Hello weifeng!
Hello weifeng!
Hello weifeng!
"""