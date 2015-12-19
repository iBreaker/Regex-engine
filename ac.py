#!/usr/bin/python
# coding:utf-8


import os
import logging


class Node(object):
    """节点"""

    def __init__(self, ggoto=dict(), failure=0, out=''):
        self.ggoto = ggoto
        self.failure = failure
        self.out = out


class AC(object):
    """ AC 算法类 """

    def __init__(self, patterns):
        self.patterns = patterns
        self.string = ''
        self.root = Node()
        pass

    def create_goto(self):
        """ 创建goto表 """

        current = self.root
        for pattern in self.patterns:
            for char in pattern:
                logging.debug("func=create_goto current char is:%c", char)
                if(not current.ggoto.has_key(char)):
                    logging.debug("func=create_goto need to create a new key:%c", char)
                    new_node = Node()
                    current.ggoto[char] = new_node
                    current = new_node
                else:
                    current = current.ggoto[char]
            current = self.root
            pass




    def create_failure(self):
        pass

    def create_out(self):
        pass

    def search(self, string):
        self.string = string
        pass


def test():
    patterns = ['he', 'she', 'his', 'hers']
    string = 'heeessisdsdfhhddihers'

    logging.basicConfig(level=logging.DEBUG,
                        format='%(asctime)s:%(levelname)s:%(message)s')
    ac = AC(patterns)
    ac.search(string)
    ac.create_goto()


if __name__ == "__main__":
    test()
