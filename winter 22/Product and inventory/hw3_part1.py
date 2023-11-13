from collections import defaultdict


def find_max_in_dict(dict_of_orders: dict, dict_of_price: dict) -> str:
    maximum = 0
    name = ""
    for k in dict_of_orders.keys():
        if dict_of_orders[k] * dict_of_price[k] > maximum:
            maximum = dict_of_orders[k] * dict_of_price[k]
            name = k
    return name


def find_max(dict_of_price: dict) -> str:
    maximum = 0
    name = ""
    for k in dict_of_price.keys():
        if dict_of_price[k] > maximum:
            maximum = dict_of_price[k]
            name = k
    return name

def find_best_selling_product(file_name: str) -> tuple:
    price_of_products = {}
    amount_products = {}
    change_amount = {}
    ship_order = defaultdict(float)
    input_file = open(file_name, 'r')
    for line in input_file:
        line_of_file = line.split()
        if line_of_file[0] == "add":
            name = line_of_file[2]
            price = float(line_of_file[3])
            amount = float(line_of_file[4])
            if price < 0 or name in price_of_products.keys() or amount < 0:
                continue
            price_of_products[name] = price
            amount_products[name] = amount
        if line_of_file[0] == "change":
            name = line_of_file[2]
            amount = float(line_of_file[3])
            change_amount[name] = float(amount)
            if name not in amount_products:
                continue
            amount_products[name] += amount
        if line_of_file[0] == "ship":
            orders_list = line.split("--")
            first_order = orders_list[0].split()
            first_order[2] = first_order[2].replace(',', '')
            order, amount = first_order[2], float(first_order[3])
            if order in amount_products.keys() and amount_products[order] - float(amount) >= 0:
                ship_order[order] += amount
                amount_products[order] -= amount
            del orders_list[0]
            for element in orders_list:
                order, amount = element.split()
                order = order.replace(',', '')
                if order not in amount_products.keys() or amount_products[order] - float(amount) < 0:
                    continue
                ship_order[order] += float(amount)
                amount_products[order] -= float(amount)
    input_file.close()
    max_products = find_max_in_dict(ship_order, price_of_products)
    if max_products == '':
        return '', 0
    return max_products, ship_order[max_products] * price_of_products[max_products]


def find_the_next_maximum(dict_of_price: dict, maximum: float) -> float:
    next_max = 0
    for k in dict_of_price.keys():
        if next_max < dict_of_price[k] < maximum:
            next_max = dict_of_price[k]
    return next_max


def products_with_same_price(dict_of_price: dict, price: float) -> list:
    products = []
    for k in dict_of_price.keys():
        if dict_of_price[k] == price:
            products += [k]
    products.sort()
    return products


def find_k_most_expensive_products(file_name: str, k: int) -> list:
    price_of_products = {}
    k_most_expensive_products = []
    if k == 0:
        return k_most_expensive_products
    input_file = open(file_name, 'r')
    for line in input_file:
        line_of_file = line.split()
        if line_of_file[0] == "add":
            name = line_of_file[2]
            price = float(line_of_file[3])
            if price < 0 or name in price_of_products.keys():
                continue
            price_of_products[name] = price
    input_file.close()
    max_price_product = find_max(price_of_products)
    if max_price_product == '':
        return []
    max_price = price_of_products[max_price_product]
    while max_price != 0:
        k_most_expensive_products += products_with_same_price(price_of_products, max_price)
        max_price = find_the_next_maximum(price_of_products, max_price)
    return k_most_expensive_products[0: k]
