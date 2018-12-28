#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


int numUniqueEmails(vector<string>& emails) {
    set<string> res;
    for(auto em : emails) {

        auto idx_at = em.find('@');
        if (idx_at == std::string::npos)
            continue;

        auto idx_plus = em.find('+');
        if (idx_plus != std::string::npos)
            em.erase(idx_plus, idx_at-idx_plus);

        idx_at = em.find('@');
        auto idx_dot = em.find('.');
        while (idx_dot != std::string::npos && idx_dot < idx_at ) {
            em.erase(idx_dot, 1);
            idx_dot = em.find('.');
            idx_at = em.find('@');
        }

        res.insert(em);
        cout << em << endl;
    }

//    for (auto em : res)
//        cout << em << endl;

    return res.size();
}

int main(int argc, char *argv[])
{
    vector<string> emails = {
    "c.o.t.m.f.q+rt.i.l@zuvn.skdsq.com",
    "d.c.fw.jc.c.gt+w@yzuq.com",
    "n.kvtb+a.iq.c.l@rupfxkfr.com",
    "xckqzemg+f.h@hbtp.com",
    "mh+f.o+k.d.e.x.fe@gywxo.n.com",
    "d.c.fw.jc.c.gt+q@yzuq.com",
    "hh.a.fm.jea.s+t@epo.com",
    "xckqzemg+dx@hbtp.com",
    "n+gz.fyk+f.oi+e@j.fe.com",
    "vqvp.p.lvt.t+k@rexcs.com",
    "nnwhgqn+qm.n@chmgo.com",
    "mrjrugbrh+e@z.zvnnhswsq.com",
    "mrjrugbrh+s@z.zvnnhswsq.com",
    "mh+fclendxh@gywxo.n.com",
    "t.bgivgn.yh+l@sytfq.mgr.com",
    "cv.oau.d.zsub+x@ybzkk.com",
    "oww.sotdsb.j+w@aadoc.r.com",
    "y.qdv+v+b+bk.di@wd.lvz.com",
    "nnwhgqn+h.se@chmgo.com",
    "nnwhgqn+fh.o@chmgo.com",
    "y.m.v.l.a+f+e+o+m+u@lhn.m.com",
    "mh+ay.gudhp+x@gywxo.n.com",
    "bvmztjceb.l+m@uci.com",
    "c.o.t.m.f.q+i.fy.v@zuvn.skdsq.com",
    "w.k.uz.n.f.u+uf+l@we.mbb.com",
    "r.s+lu.b.v.x.t.d+g@yyb.dw.com",
    "hh.a.fm.jea.s+a@epo.com",
    "t.bgivgn.yh+o@sytfq.mgr.com",
    "y.qdv+z.gyuga@wd.lvz.com",
    "mh+icx.pgzdt@gywxo.n.com",
    "y.m.v.l.a+m.p+h+as@lhn.m.com",
    "xckqzemg+w+k@hbtp.com",
    "y.m.v.l.a+tt.o+h.t@lhn.m.com",
    "n+l+mcpqdu.th@j.fe.com",
    "w.k.uz.n.f.u+s+dg@we.mbb.com",
    "e.pp.o.btp+g+k+v@qqnxdkht.com",
    "q.y+epj.qb.u.vd@rq.wxd.com",
    "u+n.p.x+zn.gv.wj@dlkmbenb.ek.com",
    "mh+dfuaping@gywxo.n.com",
    "mrjrugbrh+d@z.zvnnhswsq.com",
    "d.c.fw.jc.c.gt+x@yzuq.com",
    "n.kvtb+e+p.uu.k@rupfxkfr.com",
    "e.pp.o.btp+ijv@qqnxdkht.com",
    "e.pp.o.btp+mew@qqnxdkht.com",
    "t.bgivgn.yh+x@sytfq.mgr.com",
    "u+t.fa.f+gtp.em@dlkmbenb.ek.com",
    "t.bgivgn.yh+u@sytfq.mgr.com",
    "hh.a.fm.jea.s+c@epo.com",
    "qro.hxljfov+i@pr.wlw.com",
    "c.o.t.m.f.q+r.x.o.w@zuvn.skdsq.com",
    "y.m.v.l.a+e.z+m.lq@lhn.m.com",
    "y.qdv+uesdrh@wd.lvz.com",
    "xckqzemg+t.n@hbtp.com",
    "mh+it+kt.lc.l+r@gywxo.n.com",
    "nnwhgqn+y.k.m@chmgo.com",
    "n.kvtb+f.v+o.gh@rupfxkfr.com",
    "c.o.t.m.f.q+k.uk.s@zuvn.skdsq.com",
    "d.c.fw.jc.c.gt+d@yzuq.com",
    "y.qdv+i.q.uikf@wd.lvz.com",
    "mvvkycizo+w@wbs.j.com",
    "w.k.uz.n.f.u+icw@we.mbb.com",
    "qro.hxljfov+m@pr.wlw.com",
    "mh+nv.m.t+p.l.a.m@gywxo.n.com",
    "y.qdv+e.piws.f@wd.lvz.com",
    "y.qdv+fd+fj+x.n@wd.lvz.com",
    "n+g.f.qv.h.c.t+q.u@j.fe.com",
    "xckqzemg+gk@hbtp.com",
    "y.qdv+f.x.f+ptr@wd.lvz.com",
    "vqvp.p.lvt.t+t@rexcs.com",
    "e.pp.o.btp+hog@qqnxdkht.com",
    "cv.oau.d.zsub+u@ybzkk.com",
    "cv.oau.d.zsub+p@ybzkk.com",
    "qro.hxljfov+o@pr.wlw.com",
    "u+jaaow.ena+e@dlkmbenb.ek.com",
    "y.m.v.l.a+m.w.egc@lhn.m.com",
    "d.c.fw.jc.c.gt+d@yzuq.com",
    "yj.g.wm+kn.m.v.t@aicgst.com",
    "xckqzemg+e.g@hbtp.com",
    "bvmztjceb.l+a@uci.com",
    "vqvp.p.lvt.t+r@rexcs.com",
    "qro.hxljfov+o@pr.wlw.com",
    "y.qdv+xathpe@wd.lvz.com",
    "mskkt+lfrso@nfxouykntm.com",
    "mh+i.koi.hrps@gywxo.n.com",
    "jc.g+i.jn.x.mrv@dna.f.com",
    "w.k.uz.n.f.u+wi.u@we.mbb.com",
    "hazmbrt.nhf+f@aztvolon.com",
    "hh.a.fm.jea.s+t@epo.com",
    "cv.oau.d.zsub+e@ybzkk.com",
    "oww.sotdsb.j+t@aadoc.r.com",
    "t.bgivgn.yh+c@sytfq.mgr.com",
    "nnwhgqn+hhf@chmgo.com",
    "e.pp.o.btp+apm@qqnxdkht.com",
    "n+ipyouibnd@j.fe.com",
    "n+y.r.ks.q.z.r.lh@j.fe.com",
    "mrjrugbrh+r@z.zvnnhswsq.com",
    "c.o.t.m.f.q+h.vt+r@zuvn.skdsq.com",
    "xckqzemg+e+v@hbtp.com",
    "c.o.t.m.f.q+o+v.e+y@zuvn.skdsq.com",
    "q.y+un.d.d.q+n+or@rq.wxd.com"
    };

    int s = numUniqueEmails(emails);
    cout << s << endl;

    return 0;
}
