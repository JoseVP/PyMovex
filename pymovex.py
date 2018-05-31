import _pymovex

class PyMovexException(Exception):
    pass


def debug(d):
    _pymovex.debug(d)

def connect(*args, **kwargs):
    import os
    response = os.system("ping -c 1 %s" %(kwargs['host']))
    if response == 0:
        return _pymovex.connect(*args, **kwargs)
    else:
        return -1

def fquery(cmd, fieldMap, outputFields=()):
    try:
        return _pymovex.fquery(cmd, fieldMap, outputFields)
    except:
        print "Exception"
        raise

def fquery_single(cmd, fieldMap, outputFields=()):
    try:
        return _pymovex.fquery_single(cmd, fieldMap, outputFields)
    except:
        print "Exception"
        raise

def close(*args, **kwargs):
    return _pymovex.close(*args, **kwargs)

def query(cmd, args):
    ffargs=[]
    for value, length in args:
        ffargs.append(("%%-%ss" % length) % value)
    fargs = "".join(ffargs)
    query = "%-15s%s" % (cmd, fargs)
    # WARNING Changed to avoid sending unnecesary whitespaces
    query = query.strip()
    return _pymovex.query(query)

def query_single(cmd,args):
    ffargs = []
    for value, length in args:
        ffargs.append(("%%-%ss" % length) % value)
    fargs = "".join(ffargs)
    query = "%-15s%s" % (cmd, fargs)
    return _pymovex.query_single(query)

def rawquery(query):
    return _pymovex.query(query)

def maxrec(num):
    query("SetLstMaxRec", ((num, 11),))
