



def test_func(A,B,C,binary):
    if binary == "ADD":
        result = (A+B == C)
    elif binary == "SUB":
        result = (A-B == C)
    elif binary == "MUL":
        result = (A*B == C)

    if result == False:
        print("\nerror\n")
        print("case : A = {}, B = {} , C = {}".format(A,B,C))

def DIV_test(A,B,Q,R):
    result1 = ( A // B == Q )
    result2 = (A % B == R)
    if result1 or result2 == False:
        print("\nerror\n")
        print("case : A = {}, B = {} , Q = {} , R = {}".format(A,B,Q,R))