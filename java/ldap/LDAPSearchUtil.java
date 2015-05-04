import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Properties;
import java.util.Set;
import java.util.TreeSet;

import javax.naming.AuthenticationException;
import javax.naming.Context;
import javax.naming.NamingEnumeration;
import javax.naming.NamingException;
import javax.naming.directory.Attribute;
import javax.naming.directory.Attributes;
import javax.naming.directory.SearchControls;
import javax.naming.directory.SearchResult;
import javax.naming.ldap.InitialLdapContext;
import javax.naming.ldap.LdapContext;

public class LDAPSearchUtil {

	public static final String LDAP_CONTEXT_FACTORY = "com.sun.jndi.ldap.LdapCtxFactory";
	public static final String LINE_SEPARATOR = System.getProperty("line.separator");
	
	private LdapContext _ldapContext;
	
	LDAPSearchUtil() {
	}
	
	public LdapContext initContext(final String ldapUrl, final String securityAuthentication, final String bindDn, final String bindPassword) 
			throws Exception {

		final Hashtable<String, String> ldapEnv = new Hashtable<String, String>(5);
		ldapEnv.put(Context.INITIAL_CONTEXT_FACTORY, LDAP_CONTEXT_FACTORY);
		ldapEnv.put(Context.SECURITY_AUTHENTICATION, securityAuthentication);
		ldapEnv.put(Context.PROVIDER_URL, ldapUrl);
		ldapEnv.put(Context.SECURITY_PRINCIPAL, bindDn);
		ldapEnv.put(Context.SECURITY_CREDENTIALS, bindPassword);
		_ldapContext = new InitialLdapContext(ldapEnv, null);
		return _ldapContext;
	}
	
	public boolean isAuthenticated() {
		if (_ldapContext == null) {
			return false;
		}
		
		return true;
	}

	public List<SearchResult> search(final String baseDn, final String ldapFilter, final String scope)
		throws Exception {
		
		if (_ldapContext == null) {
			return null;
		}

		NamingEnumeration<SearchResult> searchResult = null;
		try {
			System.out.println(String.format("Requesting LDAP search for {baseDn: %s, filter: %s, scope: %s}", baseDn, ldapFilter, scope));
			
			_ldapContext.setRequestControls(null);
			searchResult = _ldapContext.search(baseDn, ldapFilter, makeSearchControl(scope));
			if (searchResult == null || !searchResult.hasMore()) {
				System.out.println(String.format("LDAP search failed for {baseDn: %s, filter: %s, scope: %s}", baseDn, ldapFilter, scope));
				throw new AuthenticationException("User does not exist");
			}
			
			List<SearchResult> resultList = new ArrayList<SearchResult>();
			while (searchResult.hasMore()) {
				resultList.add(searchResult.next());
			}
			System.out.println(String.format("LDAP search generated result {count: %d, baseDn: %s, filter: %s, scope: %s}", 
					resultList.size(), baseDn, ldapFilter, scope));
			return resultList;
		} finally {
			if (searchResult != null) {
				try { searchResult.close(); } catch (Exception e) {}
			}
		}
	}
	
	private SearchControls makeSearchControl(final String scope) {
		int scopeVal = SearchControls.SUBTREE_SCOPE;
		if (scope.equalsIgnoreCase("ONE")) {
			scopeVal = SearchControls.ONELEVEL_SCOPE;
		} else if (scope.equalsIgnoreCase("OBJECT")) {
			scopeVal = SearchControls.OBJECT_SCOPE;
		}
		
		SearchControls sc = new SearchControls();
		sc.setSearchScope(scopeVal);
		sc.setTimeLimit(10*1000);
		return sc;
	}
	
	public void close() throws Exception {
		if (_ldapContext != null) {
			_ldapContext.close();
		}
	}
	
	public Set<String> getValues(SearchResult se, String name) {
		Set<String> valueList = new TreeSet<String>(String.CASE_INSENSITIVE_ORDER);
		
		
		try {
			NamingEnumeration<? extends Attribute> aList = se.getAttributes().getAll();
			while (aList.hasMore()) {
				Attribute a = aList.next();
				if (a.getID().equalsIgnoreCase(name)) {
					NamingEnumeration<?> vList = a.getAll();
					while (vList.hasMore()) {
						valueList.add(vList.next().toString());
					}
				}
			}
		} catch (NamingException e) {
			e.printStackTrace();
		}
		return valueList;
	}
	
	public String toldif(SearchResult se) {
		Attributes aList = se.getAttributes();
		NamingEnumeration<String> idList = aList.getIDs();
		
		StringBuilder sb = new StringBuilder();
		sb.append("dn: ").append(se.getNameInNamespace()).append(LINE_SEPARATOR);
		
		try {
			while (idList.hasMore()) {
				String id = idList.next();
				Attribute a = aList.get(id);
				NamingEnumeration<?> valueList = a.getAll();
				while (valueList.hasMore()) {
					Object value = valueList.next();
					sb.append(a.getID()).append(": ").append(value.toString()).append(LINE_SEPARATOR);
				}
			}
		} catch (NamingException e) {
			e.printStackTrace();
		}
		return sb.toString();
	}

	public static void main(String[] args) {
		// ldapsearch -LLL -H ldap://localhost -b dc=aks,dc=com -x -w akspass -D cn=Manager,dc=aks,dc=com -s sub '(objectclass=*)'
		if (args.length == 0) {
			System.out.println("Incorrect usage");
			System.out.println("Usage: <java command> <class> <propertyFile>");
			System.exit(1);
		}
		
		
		LDAPSearchUtil ldap = null;
		Properties propFile = new Properties();
		try {
			propFile.load(LDAPSearchUtil.class.getClassLoader().getResourceAsStream(args[0]));
			String ldapUrl = propFile.getProperty("mms.url", "");
			String bindDn = propFile.getProperty("mms.bindDn", "");
			String bindPassword = propFile.getProperty("mms.bindPassword", "");
			String securityAuthentication = propFile.getProperty("securityAuthentication", "simple");
			String baseDn = propFile.getProperty("mms.user.baseDn", "");
			String searchAttribute = propFile.getProperty("mms.user.searchAttribute", "");
			String groupAttribute = propFile.getProperty("mms.user.group", "");
			String ownerRole = propFile.getProperty("mms.global.role.owner", "");
			String username = propFile.getProperty("ldapUser.username", "");
			
			String searchFilter = searchAttribute + "=" + username;
			//searchFilter = "(objectclass=*)";
			
			System.out.println(String.format("Running with options {url: %s, bindDn: %s, bindPassword: %s, securityAuthentication: %s, baseDn: %s, "
					+ "searchAttribute: %s, groupAttribute: %s, ownerRole: %s, searchFilter: %s}", ldapUrl, bindDn, bindPassword, 
					securityAuthentication, baseDn, searchAttribute, groupAttribute, ownerRole, searchFilter));
			
			ldap = new LDAPSearchUtil();
			ldap.initContext(ldapUrl, securityAuthentication, bindDn, bindPassword);
			System.out.println(String.format("Successfully created context using {auth: %s, bindDn: %s, bindPassword: %s}",
					securityAuthentication, bindDn, bindPassword));
			if (!ldap.isAuthenticated()) {
				System.out.println("Failed to authenticate to the LDAP.");
			}
			
			
			List<SearchResult> resultList = ldap.search(baseDn, searchFilter, "sub");
			if (resultList.size() == 0) {
				System.out.println(String.format("ERROR: Failed to lookup the user for the specified criteria {baseDn: %s, searchFilter: %s}",
						baseDn, searchFilter));
				
			} else if (resultList.size() == 1) {
				String userPassword = propFile.getProperty("ldapUser.userPassword", "");
				String userDn = resultList.get(0).getNameInNamespace();
				System.out.println(String.format("Looking for group attribute for user {userDn: %s, groupAttribute: %s, valueFound: %s}",
						userDn, groupAttribute, ldap.getValues(resultList.get(0), groupAttribute)));
				
				LDAPSearchUtil userAuthLdap = null;
				
				try {
					userAuthLdap = new LDAPSearchUtil();
					userAuthLdap.initContext(ldapUrl, securityAuthentication, userDn, userPassword);
					System.out.println(String.format("Successfully created context using {auth: %s, userDn: %s, userPassword: %s}",
							securityAuthentication, userDn, userPassword));
					System.out.println(ldap.toldif(resultList.get(0)));
				} catch (Exception e) {
					System.out.println(String.format("FATAL: Failed to create context / auth for the user authentication credentials"
							+ " {auth: %s, userDn: %s, userPassword: %s} error: %s",
							securityAuthentication, userDn, userPassword, e.getMessage()));
					e.printStackTrace();
				} finally {
					if (userAuthLdap != null) {
						try { userAuthLdap.close(); } catch (Exception e1) {}
					}
				}

			} else {
				System.out.println(String.format("ERROR: Multiple search results returned for the serach criteria, printing all namespace "
						+ "without any further user authentication checks that are expected {baseDn: %s, searchFilter: %s}", baseDn,
						searchFilter));
				for (SearchResult searchResult : resultList) {
					System.out.println(String.format("Search Result: DN: %s", searchResult.getNameInNamespace()));
					System.out.println(ldap.toldif(searchResult));
				}
			}
		} catch (Exception e) {
			System.out.println("FATAL: Exception raised in process: " + e);
			e.printStackTrace();
		} finally {
			if (ldap != null) {
				try {
					ldap.close();
				} catch (Exception e) {
				}
			}
		}
	}
}