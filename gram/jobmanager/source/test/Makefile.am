SUBDIRS = . client jobmanager

check_DATA = \
        testcred.key \
        testcred.cert \
        testcred.link

testcred.key:
	openssl genrsa -out $@ 1024 && chmod 0600 $@

.key.req:
	printf "NA\nNA\nNA\nNA\nNA\nNA\nNA\n\n\n\n" | openssl req -new -key $< -out $@

.req.cert:
	openssl x509 -req -days 365 -in testcred.req -signkey testcred.key -out $@

.cert.link:
	linkname="`openssl x509 -hash -noout -in $<`.0"; \
	rm -f "$$linkname"; \
	cp testcred.cert "$$linkname"; \
	echo "$$linkname" > $@

CLEANFILES = testcred.key testcred.cert
clean-local:
	@if test [ -r testcred.link ]; then \
            rm -f $$(cat testcred.link) testcred.link ; \
        fi
SUFFIXES = .req .cert .key .link