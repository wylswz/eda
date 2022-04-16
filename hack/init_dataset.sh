#!/bin/bash
export ETCDCTL_API=3
etcdctl put /xmbsmdsj.co.uk/a      t1
etcdctl put /xmbsmdsj.co.uk/a/b    t2
etcdctl put /xmbsmdsj.co.uk/a/b/c  t3
etcdctl put /xmbsmdsj.co.uk/a/b/d  t4
etcdctl put /xmbsmdsj.co.uk/a/c    t5
etcdctl put /xmbsmdsj.co.uk/a/d    t6
etcdctl put /xmbsmdsj.co.uk/z/x/x  t7
etcdctl put /xmbsmdsj.co.uk/z/x/c  t8
etcdctl put /xmbsmdsj.co.uk/z      t9
etcdctl put /xmbsmdsj.co.uk/       t10
